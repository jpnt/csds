# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

# Directories
BUILD_DIR = build
SRC_DIR = src
TESTS_DIR = tests

# List of files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# List of test files
TEST_SRCS = $(wildcard $(TESTS_DIR)/*.c)
TEST_EXES = $(patsubst $(TESTS_DIR)/%.c,$(BUILD_DIR)/tests/%,$(TEST_SRCS))

# Main executable
MAIN_EXE = $(BUILD_DIR)/main.out

.PHONY: all clean test

all: $(MAIN_EXE)

$(MAIN_EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(BUILD_DIR) $(OBJS) $(TEST_OBJS)
	$(foreach test_src,$(TEST_SRCS), $(CC) $(CFLAGS) $(OBJS) $(test_src) -o $(BUILD_DIR)/tests/$(notdir $(test_src:.c=)) && ./$(BUILD_DIR)/tests/$(notdir $(test_src:.c=));)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/tests

clean:
	rm -rf $(BUILD_DIR)
