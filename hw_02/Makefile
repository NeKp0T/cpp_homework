TARGET = main
TEST_TARGET = board_test
COMP = g++
CXXFLAGS = -Wall -Wextra -Wshadow -Werror -g -std=c++11
SRC = $(patsubst %, src/%, Board.cpp BoardView.cpp Test.cpp BoardTest.cpp)
INCLUDE_PATH = include
BIN_PATH = bin
SRC_PATH = src
TESTSRC_PATH = test

OBJ = $(SRC:src/%.cpp=$(BIN_PATH)/%.o)	

VPATH = $(SRC_PATH):$(BIN_PATH):$(INCLUDE_PATH)

all: $(TARGET)	

$(TEST_TARGET) : $(OBJ) $(BIN_PATH)/test.o
	$(COMP) $(OBJ) $(BIN_PATH)/test.o -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

valg_test: $(TARGET)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(TARGET)

show:
	echo "OBJ"
	echo $(OBJ)
	echo "SRC"
	echo $(SRC)

$(TARGET): $(OBJ) $(BIN_PATH)/main.o
	$(COMP) $(OBJ) $(BIN_PATH)/main.o -o $@

$(BIN_PATH)/main.o: $(SRC_PATH)/main.cpp
	mkdir -p $(BIN_PATH) 
	$(COMP) -c $(CXXFLAGS) $< -I${INCLUDE_PATH} -o $@


$(BIN_PATH)/BoardView.o: $(SRC_PATH)/BoardView.cpp
	mkdir -p $(BIN_PATH) 
	$(COMP) -c $(CXXFLAGS) $< -I${INCLUDE_PATH} -o $@


$(BIN_PATH)/Board.o: $(SRC_PATH)/Board.cpp
	mkdir -p $(BIN_PATH) 
	$(COMP) -c $(CXXFLAGS) $< -I${INCLUDE_PATH} -o $@

$(BIN_PATH)/BoardTest.o: $(TESTSRC_PATH)/BoardTest.cpp
	mkdir -p $(BIN_PATH) 
	$(COMP) -c $(CXXFLAGS) $< -I${INCLUDE_PATH} -o $@

$(BIN_PATH)/Test.o: $(TESTSRC_PATH)/Test.cpp
	mkdir -p $(BIN_PATH) 
	$(COMP) -c $(CXXFLAGS) $< -I${INCLUDE_PATH} -o $@

$(BIN_PATH)/test.o: $(TESTSRC_PATH)/test.cpp
	mkdir -p $(BIN_PATH) 
	$(COMP) -c $(CXXFLAGS) $< -I${INCLUDE_PATH} -o $@

# $^ это все зависимости через пробел, $< - первая

%.h:

bin/*.o: include/*.h
bin/main.o: include/*.h

clean: 
	rm -rf $(BIN_PATH) $(TARGET) $(TEST_TARGET)
	
.PHONY: all clean show run test	
# прописываются команды, не делающие реальный файл