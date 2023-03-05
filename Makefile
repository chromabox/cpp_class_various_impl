
CC        = $(CROSS_COMPILE)g++

all: 
	cd ./ringbuffer && make all
	cd ./threadpool && make all

clean: 
	cd ./ringbuffer && make clean
	cd ./threadpool && make clean


