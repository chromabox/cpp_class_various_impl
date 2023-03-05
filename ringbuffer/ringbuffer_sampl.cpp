//
// ringbuffer
// リングバッファの実装サンプル
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

#include "ringbuffer.hpp"

#include <iostream>
#include <vector>

using namespace std;
typedef RingBuffer<int>			RingBuffer_integer;

int main(void)
{
	RingBuffer_integer buffer(5);
	int i;
	for(i = 0; i < 7; i++){
		cout << "push ringbuffer" << i << endl;
		if(buffer.is_full()){
			cout << "Buffer is full." << endl;
		}
		buffer.push(i);
	}
	for(i = 0; i < 7; i++){
		cout << "pop ringbuffer" << i << endl;
		if(buffer.is_empty()){
			cout << "Buffer is empty." << endl;
		}
		cout << buffer.pop() << endl;
	}
	return 0;
}
