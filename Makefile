BIN=main
CC=clang++
HPP=src/async_queue.hpp src/parallel.hpp

all: $(HPP) main.cpp
	mkdir -p out/
	$(CC) -O3 -g -Wall -std=c++11 main.cpp -o "out/$(BIN)" -I src/
	cp out/$(BIN) $(CURDIR)

test:
	cd test && clang++ -std=c++11 -I /Users/mlloreda/googletest/googletest/include/ -pthread main.cpp /Users/mlloreda/googletest/googletest/lib/libgtest.a -I . -I ../src && ./a.out

clean:
	rm -rf out/ && rm $(BIN)

.PHONY: all test
