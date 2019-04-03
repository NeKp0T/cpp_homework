TARGET = lab4
CFLAGS = -Wall -Wextra -Wshadow -Werror -g
#SRC = src/main.c src/io.c src/algorithm.c src/util.c
SRC = $(patsubst %, src/%, ms_cli.c mergesort.c)
INCLUDE_PATH = include
BIN_PATH = bin
SRC_PATH = src

OBJ = $(SRC:src/%.c=$(BIN_PATH)/%.o)	

VPATH = $(SRC_PATH):$(BIN_PATH):$(INCLUDE_PATH)

all: $(TARGET)	

run: $(TARGET)
	./$(TARGET)

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

bin/%.c: str/%.h
src/ms_cli.c: ms_cli.h mergesort.h
src/mergesort.c: mergesort.h

%.h:

clean: 
	rm -rf $(BIN_PATH) $(TARGET)
	
.PHONY: all clean show run
# прописываются команды, не делающие реальный файл