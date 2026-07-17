#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "../game_states/game_state.h"

typedef struct Game Game;
typedef struct Stack Stack;
typedef struct Node Node;

typedef struct StateManager {
    Stack *states;
} StateManager;

StateManager *state_manager_create();
void state_manager_destroy(StateManager *state_manager);
void state_manager_push(StateManager *state_manager, GameState *state, Game *game);
void state_manager_pop(StateManager *state_manager, Game *game);
void state_manager_update(StateManager *state_manager, Game *game, Node *prev_state);
void state_manager_render(StateManager *state_manager, Game *game, Node *prev_state);
GameState *state_manager_peek(StateManager *state_manager);

#endif // STATE_MANAGER_H