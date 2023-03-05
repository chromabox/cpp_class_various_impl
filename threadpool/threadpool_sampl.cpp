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

#include <iostream>
#include "threadpool.hpp"

using namespace std;

// タスク１サンプル
void task1(int n)
{
	std::cout << "Task 1 executed with argument " << n << std::endl;
}

// タスク２サンプル
void task2()
{
	std::cout << "Task 2 executed" << std::endl;
}

int main(void)
{
	ThreadPool pool(2);				// スレッドプール起こす

	pool.enqueue(task1, 42);		// タスク1を入れる。poolはすぐに実行する
	pool.enqueue(task2);			// タスク2を入れる。poolはすぐに実行する

	return 0;
}

