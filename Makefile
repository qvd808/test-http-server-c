CC = gcc
CFLAGS = 
SRC_DIR = src
BIN_DIR = bin
TEST_DIR = test

TEST_FILES=$(wildcard $(TEST_DIR)/*.c)
TEST_EXEC=$(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%.o, $(TEST_FILES))

EXECUTABLES=\
$(BIN_DIR)/server.o \
$(BIN_DIR)/client.o\

all: $(EXECUTABLES)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(TEST_EXEC)

$(BIN_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BIN_DIR)/*.o
	rm -f $(TEST_DIR)/*.o
