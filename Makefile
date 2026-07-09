# --- BUILD CONFIGURATIONS ---
CC = gcc
# Added -D__USE_MINGW_ANSI_STDIO=1 to fix the %zu printf warnings on Windows
CFLAGS = -Wall -Wextra -O2 -Isrc -Itests -D__USE_MINGW_ANSI_STDIO=1

# --- DIRECTORIES ---
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# --- AUTOMATIC FILE MAPPING ---
# Using native Make wildcard function (no $(shell ...)) to prevent CreateProcess errors
SRC_SOURCES   := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
TEST_SOURCES  := $(wildcard $(TEST_DIR)/*.c) $(wildcard $(TEST_DIR)/*/*.c)

# Removes utils_test.c from the main test list to avoid conflicts with main_test
TEST_SOURCES  := $(filter-out $(TEST_DIR)/utils_test.c, $(TEST_SOURCES))

# Transforms .c file paths into equivalent .o paths inside build/
SRC_OBJS      := $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SRC_SOURCES)))
TEST_OBJS     := $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(TEST_SOURCES)))

# --- SEARCH DIRECTORIES (VPATH) ---
# Hardcoded subdirectories to avoid breaking on Windows CMD with Linux 'find'
VPATH = $(SRC_DIR):$(SRC_DIR)/graphics:$(SRC_DIR)/core:$(SRC_DIR)/input:$(SRC_DIR)/world:$(SRC_DIR)/objects:$(SRC_DIR)/physics:$(SRC_DIR)/utils:$(SRC_DIR)/persistence:$(SRC_DIR)/managers:$(TEST_DIR):$(TEST_DIR)/graphics_tests:$(TEST_DIR)/physics_tests:$(TEST_DIR)/core_tests:$(TEST_DIR)/input_tests:$(TEST_DIR)/world_tests:$(TEST_DIR)/objects_tests:$(TEST_DIR)/utils

# --- MAIN RULES ---
.PHONY: all test test_utils clean

all: test

# Main Game Tests Target
test: $(SRC_OBJS) $(TEST_OBJS)
	$(CC) -o $(TEST_DIR)/run_tests $^

# Isolated Target for Utility Tests (Vector)
test_utils: $(BUILD_DIR)/utils_test.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/vector.o
	$(CC) -o $(TEST_DIR)/run_utils_tests $^

# --- PATTERN RULES ---
$(BUILD_DIR)/%.o: %.c
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- CLEANUP ---
clean:
	@if exist $(BUILD_DIR)\*.o del /q $(BUILD_DIR)\*.o
	@if exist $(BUILD_DIR)\*.exe del /q $(BUILD_DIR)\*.exe
	@if exist $(TEST_DIR)\run_tests del /q $(TEST_DIR)\run_tests
	@if exist $(TEST_DIR)\run_tests.exe del /q $(TEST_DIR)\run_tests.exe
	@if exist $(TEST_DIR)\run_utils_tests del /q $(TEST_DIR)\run_utils_tests
	@if exist $(TEST_DIR)\run_utils_tests.exe del /q $(TEST_DIR)\run_utils_tests.exe