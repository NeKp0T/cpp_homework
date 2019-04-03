TARGET = main
CFLAGS = -Wall -Wextra -Wshadow -Werror -g
#SRC = src/main.c src/io.c src/algorithm.c src/util.c
SRC = $(patsubst %, src/%, main.c clist.c position.c)
INCLUDE_PATH = include
BIN_PATH = bin
SRC_PATH = src

OBJ = $(SRC:src/%.c=$(BIN_PATH)/%.o)	

VPATH = $(SRC_PATH):$(BIN_PATH):$(INCLUDE_PATH)

all: $(TARGET)	

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./main loadtext f.txt savetext fout.txt loadtext fout.txt print "%d %d | " savebin b loadbin b print "[%d %d] " count

valg_test: $(TARGET)
	valgrind --tool=memcheck --leak-check=full ./$(TARGET)

show:
	echo "OBJ"
	echo $(OBJ)
	echo "SRC"
	echo $(SRC)

$(TARGET): $(OBJ)
	gcc $(OBJ) -o $@

$(BIN_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(BIN_PATH) 
	gcc -c $(CFLAGS) $< -I${INCLUDE_PATH} -o $@

# $^ это все зависимости через пробел, $< - первая

%.h:

bin/%.c: str/%.h
bin/main.c: clist.h

clean: 
	rm -rf $(BIN_PATH) $(TARGET) fout.txt b
	
.PHONY: all clean show run test	
# прописываются команды, не делающие реальный файл