CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -Werror -std=c++03 -Iinclude -Itest -Isrc -g -pedantic -std=c++14
LDFLAGS = 

TEST_TARGET = test.elf
EXE = huffman
SRCDIR = src
BINDIR = bin
TESTDIR = test

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp)) 
TESTOBJ = $(patsubst $(TESTDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(TESTDIR)/*.cpp))

all: $(EXE)

$(TEST_TARGET) : bin/huffman.o bin/bitio.o $(TESTOBJ) $(BINDIR)/test.o
	$(CXX) $^ -o $@ $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(EXE)
	./$(EXE) -u < coded

valg_test: $(EXE)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(EXE) -c -v -f src/huffman.cpp -o arch
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(EXE) -u -v -f arch -o cphuffman
	diff cphuffman src/huffman.cpp

$(EXE): $(OBJECTS)
	echo "$(OBJECTS)"
	$(CXX) $^ -o $(EXE) $(LDFLAGS)

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)
	
$(BINDIR)/%.o: $(SRCDIR)/%.cpp $(BINDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(BINDIR)/%.o: $(TESTDIR)/%.cpp $(BINDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

clean:
	rm -rf $(BINDIR) $(EXE) smoke *.edb

.PHONY: clean all run valg_test
