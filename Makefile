# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -fanalyzer -std=c90 -pedantic -Iinclude
# CC = clang
# CFLAGS = -g -Wall -Wextra -Xanalyzer -std=c90 -pedantic -Iinclude

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

# Valgrind flags
VALGRIND = valgrind
VALGRIND_FLAGS = --leak-check=full --track-origins=yes --show-reachable=yes -s

.PHONY: all clean test valgrind

all: $(BUILD_DIR) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(BUILD_DIR) $(OBJS) $(TEST_EXES)
	$(foreach test,$(TEST_EXES), $(test);)

valgrind: $(BUILD_DIR) $(OBJS) $(TEST_EXES)
	$(foreach test,$(TEST_EXES), $(VALGRIND) $(VALGRIND_FLAGS) $(test);)

$(BUILD_DIR)/tests/%: $(TESTS_DIR)/%.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/tests

clean:
	rm -rfv $(BUILD_DIR)
