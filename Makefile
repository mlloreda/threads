all:	async_queue.hpp parallel.hpp test.cpp
	clang++ -O3 -g -Wall -std=c++11 test.cpp -o t
