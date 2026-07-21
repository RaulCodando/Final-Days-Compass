#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>

typedef struct Game Game;

typedef enum GameStateType {
    STATE_PLAYING,
    STATE_MENU
} GameStateType;

typedef struct GameState {
    GameStateType type;
    
    bool update_lower_state;
    bool render_lower_state;

    void *state_data;
    
    void (*enter) (Game *game, void *state_data);
    void (*exit) (Game *game, void *state_data);
    void (*update) (Game *game, void *state_data);
    void (*render) (Game *game, void *state_data);
} GameState;

void game_state_destroy(GameState *state);

#endif // GAME_STATE_H