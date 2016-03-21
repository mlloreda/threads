all:	async_queue.hpp parallel.hpp test.cpp
	clang++ -pthread -O0 -g -Wall --std=c++11 test.cpp -o test
