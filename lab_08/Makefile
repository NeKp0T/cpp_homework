.PHONY: all clean

CXX=g++ -std=c++11
CXXFLAGS=-Wall -pedantic -g

all: main

run: main
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./main

bin:
	mkdir -p bin

main: src/main.cpp bin/matrix.o include/*.h bin
	$(CXX) $(CXXFLAGS) -o $@ -Iinclude $< bin/*

bin/%.o: src/%.cpp include/*.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ -Iinclude $<

clean:
	rm -rf bin main run
