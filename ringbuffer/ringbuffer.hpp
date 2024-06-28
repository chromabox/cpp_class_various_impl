#pragma once

//
// ringbuffer
// c++ STLによるリングバッファの実装
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

#include <vector>

using namespace std;

template<class _T>
class RingBuffer {
private:
	vector<_T> buffer;			// リングバッファの本体。vectorが実体
	size_t head;				// 最初のインデックス
	size_t tail;				// 末尾のインデックス
	size_t capacity;			// キャパ

public:
	// リングバッファの初期化を行うコンストラクタ
	// size = デカさ
	RingBuffer(size_t size)
	{
		buffer.resize(size+1);
		head = 0;
		tail = 0;
		capacity = size+1;
	}

	// リングバッファの最後にオブジェクトを追加する
	// 最終に達してしまった場合は先頭の指し示している箇所に上書きする
	// value: リングバッファに追加したいオブジェクト
	void push(_T value)
	{
		buffer[tail] = value;
		tail = (tail + 1) % capacity;
		if (tail == head) {
			head = (head + 1) % capacity;
		}
	}

	// リングバッファの現在の先頭からオブジェクトを取り出す
	// 全部取り出してしまった場合は先頭を返す
	// TODO:もしかしたら全部取り出しは例外投げたほうがいいのかもしれない
	_T pop()
	{
		if (head == tail) {
			return buffer[head];
		}
		_T value = buffer[head];
		head = (head + 1) % capacity;
		return value;
	}

	// リングバッファが空かどうか
	bool is_empty()
	{
		return head == tail;
	}

	// リングバッファが満杯かどうか
	bool is_full()
	{
		return (tail + 1) % capacity == head;
	}
};
