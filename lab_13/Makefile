CXX = g++
CXXFLAGS = -O0 -Wall -Wextra -Werror -std=c++03 -Iinclude -g -pedantic
LDFLAGS = 

EXE = main
SRCDIR = src
BINDIR = bin

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

run: $(EXE)
	./$(EXE)

smoke: $(BINDIR)/smoke_compile.o
	$(CXX) $< -o $@ $(LDFLAGS)

valg_test: $(EXE)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(EXE)

$(EXE): $(BINDIR)/$(EXE).o
	$(CXX) $< -o $(EXE) $(LDFLAGS)

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)
	
$(BINDIR)/%.o: $(SRCDIR)/%.cpp $(BINDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

clean:
	rm -rf $(BINDIR) $(EXE) smoke *.edb

.PHONY: clean all run valg_test
