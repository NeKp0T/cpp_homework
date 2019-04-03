CXX = g++
CXXFLAGS = -O0 -Wall -Wextra -Werror -std=c++03 -Iinclude -g -pedantic -std=c++11
LDFLAGS = 

EXE = main
SRCDIR = src
BINDIR = bin

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

run: $(EXE)
	./$(EXE)

valg_test: $(EXE)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(EXE)

$(EXE): $(OBJECTS)
	echo "$(OBJECTS)"
	$(CXX) $^ -o $(EXE) $(LDFLAGS)

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)
	
$(BINDIR)/%.o: $(SRCDIR)/%.cpp $(BINDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

clean:
	rm -rf $(BINDIR) $(EXE) smoke *.edb

.PHONY: clean all run valg_test
