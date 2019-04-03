CXX = g++
CXXFLAGS = -O0 -Wall -Wextra -Iinclude -g -pedantic -std=c++14
LDFLAGS = 

all: test

run: smoke_test
	./smoke_test

valg_test: main
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./main
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./min_smoke_test
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./smoke_test

test: smoke_test min_smoke_test main
	./main
	./min_smoke_test
	./smoke_test

smoke_test: smoke_test.cpp include/linq.h
	$(CXX) smoke_test.cpp -o $@ $(CXXFLAGS)

min_smoke_test: minimal_smoke_test.cpp include/linq.h
	$(CXX) minimal_smoke_test.cpp -o $@ $(CXXFLAGS)

main: main.cpp include/linq.h
	$(CXX) main.cpp -o $@ $(CXXFLAGS)

clean:
	rm -rf *smoke* *.edb main

.PHONY: clean all run valg_test test
