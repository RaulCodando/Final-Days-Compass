#include "playing_state.h"
#include "menu_state.h"
#include "../core/game.h"
#include "../input/commands.h"
#include "../entity_behaviors/generic_entity_behaviors.h"
#include "../core/state_manager.h"
#include <stdlib.h>
#include <math.h>



static void playing_state_enter(Game *game){
    
}

static void playing_state_exit(Game *game){
    
}

static void playing_state_update(Game *game){
    if(!game || !game->entities) return;

    if (game->commands.quit_game.triggered) {
        game->commands.quit_game.triggered = false;

        state_manager_push(game->state_manager, menu_state_create(), game);
        return;
    }

    Entity *player = NULL;
    int map_width_px = game->map->width * game->map->tile_size;
    int map_height_px = game->map->height * game->map->tile_size;

    for (size_t i = 0; i < game->entities->size; i++) {
        Entity *entity = (Entity *)vector_get(game->entities, i);
        if(entity == NULL) continue;
        entity->vel_x = 0.0f;
        entity->vel_y = 0.0f;
        if(entity->base.id == PLAYER) player = entity;
    }

    if(player == NULL) return;

    for (size_t i = 0; i < game->entities->size; i++) {
        Entity *entity = (Entity *)vector_get(game->entities, i);
        if(entity == NULL || entity->update_behavior == NULL) continue;
        
        entity->update_behavior(entity, game);
        if(entity->vel_x != 0.0f || entity->vel_y != 0.0f) wrap_around_map(entity, map_width_px, map_height_px);
    }

    camera_update(game->camera, player->x_pos, player->y_pos, player->base.sprite->width, player->base.sprite->height, map_width_px, map_height_px);
}

static void playing_state_render(Game *game){
    if(!game || !game->entities) return;

    if (game->map != NULL) {
        renderer_draw_map(game->renderer, game->camera, game->map);
    }

    for(size_t i = 0; i < game->entities->size; i++){
        Entity *entity = (Entity*)vector_get(game->entities, i);
        if (!entity) continue;
        
        int entity_screen_x = (int) floorf(entity->x_pos - game->camera->x);
        int entity_screen_y = (int) floorf(entity->y_pos - game->camera->y);

        renderer_draw(game->renderer, entity_screen_x, entity_screen_y, entity->base.sprite);
    }
}

GameState *playing_state_create(){
    GameState *state = malloc(sizeof(GameState));
    if(state == NULL) return NULL;
    state->type = STATE_PLAYING;
    state->update_lower_state = false;
    state->render_lower_state = false;
    state->enter = playing_state_enter;
    state->exit = playing_state_exit;
    state->update = playing_state_update;
    state->render = playing_state_render;
    return state;
}