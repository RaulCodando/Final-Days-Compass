#include "menu_state.h"
#include "../core/game.h"

static void menu_state_enter(Game *game){
    
}

static void menu_state_exit(Game *game){
    
}

static void menu_state_update(Game *game){
    if(!game) return;
    
    if (game->commands.quit_game.triggered) {
        game->commands.quit_game.triggered = false;
        
        state_manager_pop(game->state_manager, game);
        return;
    }
}

static void menu_state_render(Game *game){
    
}

GameState *menu_state_create(){
    GameState *state = malloc(sizeof(GameState));
    if(state == NULL) return NULL;
    state->type = STATE_MENU;
    state->update_lower_state = false;
    state->render_lower_state = true;
    state->enter = menu_state_enter;
    state->exit = menu_state_exit;
    state->update = menu_state_update;
    state->render = menu_state_render;
    return state;
}