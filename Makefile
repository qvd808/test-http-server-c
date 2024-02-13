CC = gcc
CFLAGS = 
SRC_DIR = src
BIN_DIR = bin
TEST_DIR = test

EXECUTABLES=\
$(BIN_DIR)/server.o \
$(BIN_DIR)/client.o\

all: $(EXECUTABLES)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BIN_DIR)/*.o
	rm -f $(TEST_DIR)/*.o

# .PHONY: print_test_files
# print_test_files:
# 	@for file in $(TEST_FILES); do \
# 		echo $$file; \
# 	done

# $(TEST_OBJS): $(TEST_FILES)
# 	$(CC) $(CFLAGS) -o $@ $<

# clean:
# 	rm -f $(BIN_DIR)/*.o
# 	rm -f $(TEST_DIR)/*.o
# $(BIN_DIR)/client.o: $(SRC_DIR)/client.c
# 	$(CC) $(CFLAGS) -o $@ $<

# $(BIN_DIR)/server.o: $(SRC_DIR)/server.c
# 	$(CC) $(CFLAGS) -o $@ $<