TARGET = main
CFLAGS = -Wall -Wextra -Wshadow -Werror -g -std=c99
#SRC = src/main.c src/io.c src/algorithm.c src/util.c
SRC = $(patsubst %, src/%, main.c bmp.c stenography.c)
INCLUDE_PATH = include
BIN_PATH = bin
SRC_PATH = src

OBJ = $(SRC:src/%.c=$(BIN_PATH)/%.o)	

VPATH = $(SRC_PATH):$(BIN_PATH):$(INCLUDE_PATH)

all: $(TARGET)	

run: $(TARGET)
	./$(TARGET)

valg_test: $(TARGET)
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET) crop-rotate bmp_source/test_image.bmp out.bmp 15 61 11 128
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET) crop-rotate bmp_source/lena_smth.bmp out2.bmp 45 45 80 80
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET) insert bmp_source/lena_smth.bmp out.bmp key.txt msg.txt
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET) extract out.bmp key.txt outmsg.txt
	cat outmsg.txt

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

bin/*.c: include/*.h
bin/*.c: include/bmp.h

clean: 
	rm -rf $(BIN_PATH) $(TARGET) *.bmp
	
.PHONY: all clean show run test valg_test	
# прописываются команды, не делающие реальный файл