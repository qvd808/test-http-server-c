CC = gcc
CFLAGS = 
SRC_DIR = src
BIN_DIR = bin
TEST_DIR = test

TEST_FILES=$(wildcard $(TEST_DIR)/*.c)
TEST_EXEC=$(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%.o, $(TEST_FILES))

SRC_FILES=$(wildcard $(SRC_DIR)/*.c)

OBJS=$(patsubst $(SRC_DIR)%.c, $(BIN_DIR)/%.o, $(SRC_FILES))


all: $(OBJS)
	gcc -c $(OBJS) -o main


$(OBJS): $(SRC_FILES)
	$(CC) -c $< -o $@

test: $(TEST_EXEC)

$(BIN_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BIN_DIR)/*.o
	rm -f $(TEST_DIR)/*.o
