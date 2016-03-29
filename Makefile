all:	src/async_queue.hpp src/parallel.hpp test.cpp
	clang++ -O3 -g -Wall -std=c++11 test.cpp -o t -I src/

test:
	cd test && clang++ -std=c++11 -I /Users/mlloreda/googletest/googletest/include/ -pthread main.cpp /Users/mlloreda/googletest/googletest/lib/libgtest.a -I . -I ../src && ./a.out

.PHONY: all test
