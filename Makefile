# --- BUILD CONFIGURATIONS ---
CC = gcc

# --- SDL3, SDL_image & SDL_ttf CONFIGURATION ---
SDL_DIR           = SDL/x86_64-w64-mingw32
SDL_INCLUDE       = $(SDL_DIR)/include
SDL_LIB           = $(SDL_DIR)/lib

SDL_IMAGE_DIR     = SDL_image/x86_64-w64-mingw32
SDL_IMAGE_INCLUDE = $(SDL_IMAGE_DIR)/include
SDL_IMAGE_LIB     = $(SDL_IMAGE_DIR)/lib

SDL_TTF_DIR       = SDL_ttf/x86_64-w64-mingw32
SDL_TTF_INCLUDE   = $(SDL_TTF_DIR)/include
SDL_TTF_LIB       = $(SDL_TTF_DIR)/lib

LIBS = -lmingw32 -lSDL3_image -lSDL3_ttf -lSDL3

CFLAGS  = -Wall -Wextra -O2 -Isrc -Itests -I$(SDL_INCLUDE) -I$(SDL_IMAGE_INCLUDE) -I$(SDL_TTF_INCLUDE)
LDFLAGS = -L$(SDL_LIB) -L$(SDL_IMAGE_LIB) -L$(SDL_TTF_LIB) -mconsole

# --- DIRECTORIES ---
SRC_DIR      = src
TEST_DIR     = tests
BUILD_DIR    = build

# --- AUTOMATIC FILE MAPPING ---
ALL_SRC_SOURCES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)

# Remove a main.c do jogo da lista de fontes comuns para não gerar duplicidade no target test
GAME_MAIN       := $(SRC_DIR)/main.c
CORE_SRC_SOURCES:= $(filter-out $(GAME_MAIN), $(ALL_SRC_SOURCES))

TEST_SOURCES    := $(wildcard $(TEST_DIR)/*.c) $(wildcard $(TEST_DIR)/*/*.c)
TEST_SOURCES    := $(filter-out $(TEST_DIR)/utils_test.c, $(TEST_SOURCES))

# Mapeia os objetos
CORE_SRC_OBJS   := $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(CORE_SRC_SOURCES)))
GAME_MAIN_OBJ   := $(BUILD_DIR)/main.o
TEST_OBJS       := $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(TEST_SOURCES)))

# --- SEARCH DIRECTORIES (VPATH) ---
VPATH = $(SRC_DIR):$(SRC_DIR)/graphics:$(SRC_DIR)/core:$(SRC_DIR)/input:$(SRC_DIR)/world:$(SRC_DIR)/objects:$(SRC_DIR)/physics:$(SRC_DIR)/utils:$(SRC_DIR)/persistence:$(SRC_DIR)/managers:$(SRC_DIR)/game_states:$(SRC_DIR)/ui:$(SRC_DIR)/entities:$(SRC_DIR)/asset_manager:$(SRC_DIR)/scenery_elements:$(TEST_DIR):$(TEST_DIR)/graphics_tests:$(TEST_DIR)/physics_tests:$(TEST_DIR)/core_tests:$(TEST_DIR)/input_tests:$(TEST_DIR)/world_tests:$(TEST_DIR)/objects_tests:$(TEST_DIR)/utils:$(TEST_DIR)/managers_tests

# --- MAIN RULES ---
.PHONY: all default test test_utils clean

all: default

# Main Game (Linka as fontes do core + a main.o do jogo principal)
default: $(CORE_SRC_OBJS) $(GAME_MAIN_OBJ)
	$(CC) -o game $^ $(LDFLAGS) $(LIBS)

# Main Game Tests Target (Linka apenas o core sem a main.o do jogo + os testes)
test: $(CORE_SRC_OBJS) $(TEST_OBJS)
	$(CC) -o $(TEST_DIR)/run_tests $^ $(LDFLAGS) $(LIBS)

# Isolated Target for Utility Tests (Vector)
test_utils: $(BUILD_DIR)/utils_test.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/vector.o
	$(CC) -o $(TEST_DIR)/run_utils_tests $^ $(LDFLAGS) $(LIBS)

# --- PATTERN RULES ---
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- CLEANUP ---
clean:
	@rm -f $(BUILD_DIR)/*.o
	@rm -f $(BUILD_DIR)/*.exe
	@rm -f game game.exe
	@rm -f $(TEST_DIR)/run_tests $(TEST_DIR)/run_tests.exe
	@rm -f $(TEST_DIR)/run_utils_tests $(TEST_DIR)/run_utils_tests.exe