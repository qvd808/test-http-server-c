CC = gcc
CFLAGS = 
SRC_DIR = src
BIN_DIR = bin
TEST_DIR = test

TEST_FILES=$(wildcard $(TEST_DIR)/*.c)
TEST_EXEC=$(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%.o, $(TEST_FILES))

SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJS= $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))



all: $(BIN_DIR)/main.o $(BIN_DIR)/request.o $(BIN_DIR)/vector.o
	gcc $(BIN_DIR)/main.o $(BIN_DIR)/request.o $(BIN_DIR)/vector.o -o $(BIN_DIR)/program.o

$(BIN_DIR)/vector.o:
	gcc -c $(SRC_DIR)/vector.c -o $(BIN_DIR)/vector.o

$(BIN_DIR)/request.o:
	gcc -c $(SRC_DIR)/request.c -o $(BIN_DIR)/request.o

$(BIN_DIR)/main.o:
	gcc -c $(SRC_DIR)/main.c -o $(BIN_DIR)/main.o

test: $(TEST_EXEC)

$(BIN_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BIN_DIR)/*.o
	rm -f $(TEST_DIR)/*.o
