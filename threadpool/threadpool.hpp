#pragma once

//
// threadpool
// c++ STLによるスレッドプールの実装
// 
// The MIT License (MIT)
//
// Copyright (c) <2023> chromabox <chromarockjp@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool
{
private:
	std::vector<std::thread> threads_;				// スレッドプール本体
	std::queue<std::function<void()>> tasks_;		// 関数タスクキュー

	std::mutex mutex_;								// プールロック用ミューテックス
	std::condition_variable condition_;
	bool stop_ = false;

public:
	// スレッドプールの初期化を行って、スレッド実行ポンプを回してゆくコンストラクタ
	// numThreads = スレッドプール内のスレッド数
	ThreadPool(size_t numThreads)
	{
		size_t i;
		for (i = 0;i < numThreads;i++){
			threads_.emplace_back([this] {
				for (;;) {
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(mutex_);
						condition_.wait(lock, [this] { return stop_ || !tasks_.empty(); });
						// ストップがかかっていてタスクが無い場合はなにもしない
						if (stop_ && tasks_.empty()) {
							return;
						}
						task = std::move(tasks_.front());
						tasks_.pop();
					}
					// タスクを実行してゆく...
					task();
				}
			});
		}
	}

	~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(mutex_);
			stop_ = true;		// これをしてポンプを止める必要がある
		}
		condition_.notify_all();
		// 終わるまで静かに待つ…
		for (auto& thread : threads_) {
			thread.join();
		}
	}

	// スレッドをキューに入れて実行を促す
	template <typename Func, typename... Args>
	void enqueue(Func&& func, Args&&... args)
	{
		std::function<void()> task(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
		{
			std::unique_lock<std::mutex> lock(mutex_);
			tasks_.emplace(task);
		}
		condition_.notify_one();
	}
};
