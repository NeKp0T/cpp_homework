CXX = g++
CXXFLAGS = -O0 -Wall -Werror -std=c++03 -Iinclude -g -std=c++11
LDFLAGS = 

EXE = empl_db
SRCDIR = src
BINDIR = bin

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

run: $(EXE)
	./$(EXE)

valg_test: $(EXE)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(EXE) < cmds

$(EXE): $(BINDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(EXE) *.edb

.PHONY: clean all run valg_test
