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
BUILD_DIR    = build

# --- PLATFORM COMMANDS ---
ifeq ($(OS),Windows_NT)
	MKDIR_CMD = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	CLEAN_OBJS = if exist $(BUILD_DIR)\*.o del /Q /F $(BUILD_DIR)\*.o
	CLEAN_EXES = if exist $(BUILD_DIR)\*.exe del /Q /F $(BUILD_DIR)\*.exe
	CLEAN_GAME = if exist game.exe del /Q /F game.exe
else
	MKDIR_CMD = mkdir -p $(BUILD_DIR)
	CLEAN_OBJS = rm -f $(BUILD_DIR)/*.o
	CLEAN_EXES = rm -f $(BUILD_DIR)/*.exe
	CLEAN_GAME = rm -f game game.exe
endif

# --- AUTOMATIC FILE MAPPING ---
ALL_SRC_SOURCES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)

# Remove a main.c do jogo da lista de fontes comuns para não gerar duplicidade no target test
GAME_MAIN       := $(SRC_DIR)/main.c
CORE_SRC_SOURCES:= $(filter-out $(GAME_MAIN), $(ALL_SRC_SOURCES))

# Mapeia os objetos
CORE_SRC_OBJS   := $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(CORE_SRC_SOURCES)))
GAME_MAIN_OBJ   := $(BUILD_DIR)/main.o

# --- SEARCH DIRECTORIES (VPATH) ---
VPATH = $(SRC_DIR):$(SRC_DIR)/graphics:$(SRC_DIR)/core:$(SRC_DIR)/input:$(SRC_DIR)/world:$(SRC_DIR)/objects:$(SRC_DIR)/physics:$(SRC_DIR)/utils:$(SRC_DIR)/persistence:$(SRC_DIR)/managers:$(SRC_DIR)/game_states:$(SRC_DIR)/ui:$(SRC_DIR)/entities:$(SRC_DIR)/asset_manager:$(SRC_DIR)/scenery_elements

# --- MAIN RULES ---
.PHONY: all default clean

all: default

# Main Game (Linka as fontes do core + a main.o do jogo principal)
default: $(CORE_SRC_OBJS) $(GAME_MAIN_OBJ)
	$(CC) -o game $^ $(LDFLAGS) $(LIBS)

# --- PATTERN RULES ---
$(BUILD_DIR)/%.o: %.c
	@$(MKDIR_CMD)
	$(CC) $(CFLAGS) -c $< -o $@

# --- CLEANUP ---
clean:
	@$(CLEAN_OBJS)
	@$(CLEAN_EXES)
	@$(CLEAN_GAME)