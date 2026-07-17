#include "state_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include "../utils/stack.h"
#include "../input/commands.h"
#include "game.h"

StateManager *state_manager_create(){
    StateManager *state_manager = (StateManager*) malloc(sizeof(StateManager));
    if(state_manager == NULL) return NULL;

    state_manager->states = stack_create();
    if(state_manager->states == NULL) {
        free(state_manager);
        return NULL;
    }
    return state_manager;
}

void state_manager_destroy(StateManager *state_manager){
    if(state_manager == NULL) return;
    stack_destroy(state_manager->states, (destroy_data_func) game_state_destroy);
    free(state_manager);
}

void state_manager_push(StateManager *state_manager, GameState *state, Game *game){
    if(state_manager == NULL || state == NULL || game == NULL) return;
    if(state->enter != NULL) state->enter(game);
    stack_push(state_manager->states, (void*) state);
}

void state_manager_pop(StateManager *state_manager, Game *game){
    if(state_manager == NULL || game == NULL) return;
    GameState *state = state_manager_peek(state_manager);
    if(state != NULL) {
        if(state->exit != NULL) state->exit(game);
        game_state_destroy(stack_pop(state_manager->states));
    }
}

void state_manager_update(StateManager *state_manager, Game *game, Node *current_state){
    if(state_manager == NULL || game == NULL || current_state == NULL) return;

    GameState *state = (GameState*)current_state->data;
    if(state == NULL || state->update == NULL) return;

    if(state->update_lower_state && current_state->next != NULL) {
        Commands original_commands = game->commands;
        commands_stop(&game->commands);
        state_manager_update(state_manager, game, current_state->next);
        game->commands = original_commands;
    }

    state->update(game);
}


void state_manager_render(StateManager *state_manager, Game *game, Node *current_state){
    if(state_manager == NULL || game == NULL || current_state == NULL) return;

    GameState *state = (GameState*)current_state->data;
    if(state == NULL || state->render == NULL) return;

    if(state->render_lower_state && current_state->next != NULL) {
        state_manager_render(state_manager, game, current_state->next);
        renderer_apply_dim(game->renderer, 2);
    }

    state->render(game);
}

GameState *state_manager_peek(StateManager *state_manager){
    if(state_manager == NULL) return NULL;
    return (GameState*) stack_peek(state_manager->states);
}