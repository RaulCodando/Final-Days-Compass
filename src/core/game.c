#include "game.h"
#include "state_manager.h"
#include "../graphics/sprite.h"
#include "../objects/asset_manager.h"
#include "../managers/window_manager.h"
#include "../managers/entity_manager.h"
#include "../managers/world_manager.h"
#include "../entity_behaviors/generic_entity_behaviors.h"
#include "../entity_behaviors/player_behavior.h"
#include "../game_states/playing_state.h"
#include "../utils/stack.h"
#include "../ui/hud.h"
#include "settings.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Game *game_create(void){
    Game *game = (Game*) malloc(sizeof(Game));
    if(game == NULL) return NULL;

    keyboard_init(&game->keyboard);
    commands_init(&game->commands);

    game->frequency = SDL_GetPerformanceFrequency();
    game->last_time = SDL_GetPerformanceCounter();
    game->camera = NULL;
    game->entities = NULL;
    game->map = NULL;
    game->renderer = NULL;
    game->solid_tile_ids.solid_tile_ids = NULL;
    game->custom_colliders = NULL;
    game->state_manager = NULL;
    game->window = NULL;
    game->solid_tile_ids.tile_count = 0;
    game->delta_time = 0.0f;
    game->accumulator = 0.0f;
    game->is_running = false;
    game->state_manager = state_manager_create();
    game->asset_manager = asset_manager_create();
    
    return game;
}

bool manage_window_init(Game *game, float camera_x, float camera_y, float dead_zone_percentage){
    if(game == NULL) return false;
    return init_window(&game->camera, &game->renderer, &game->window, camera_x, camera_y, dead_zone_percentage);
}

bool manage_entities_init(Game *game){
    if(game == NULL) return false;    
    return init_entities(&game->entities);
}

bool manage_entities_add(Game *game, Entity* entity){
    if(game == NULL) return false;
    return add_entity(&game->entities, entity);
}

bool manage_world_init(Game *game, const char *map_file, int tile_size, char *tile_ids, int tile_count, SDL_Color tile_color){
    if(game == NULL) return false;
    return init_world(game->renderer->sdl_renderer, &game->map, &game->solid_tile_ids, map_file, tile_size, tile_ids, tile_count, tile_color);
}

bool manage_world_colliders_init(Game *game){
    if(game == NULL) return false;
    return init_colliders(&game->custom_colliders);
}

bool manage_world_colliders_add(Game *game, float x, float y, float width, float height){
    if(game == NULL) return false;
    return add_collider(&game->custom_colliders, x, y, width, height);
}

void game_destroy(Game *game){
    if(game == NULL) return;

    if (game->entities != NULL) vector_destroy(game->entities, (destroy_data_func)entity_destroy);
    if (game->custom_colliders != NULL) vector_destroy(game->custom_colliders, (destroy_data_func)collider_destroy);
    if (game->map != NULL) map_destroy(game->map);
    if (game->camera != NULL) camera_destroy(game->camera);
    if (game->asset_manager != NULL) asset_manager_destroy(game->asset_manager);
    if (game->renderer != NULL) renderer_destroy(game->renderer);
    if (game->state_manager != NULL) state_manager_destroy(game->state_manager);
    if (game->window != NULL) SDL_DestroyWindow(game->window);

    solid_tile_ids_destroy(&game->solid_tile_ids);

    free(game);
}

void game_update(Game *game){
    if(!game) return;

    if(!game->state_manager) return;
    state_manager_update(game->state_manager, game, game->state_manager->states->top);
}

void game_draw(Game *game){
    if(!game) return;
    if(!game->state_manager) return;
    if(game->renderer) renderer_clear(game->renderer);
    state_manager_render(game->state_manager, game, game->state_manager->states->top);
    if(game->renderer) renderer_present(game->renderer);
}

void game_loop(Game *game) {
    Uint64 current_time = SDL_GetPerformanceCounter();
    float frame_time = (float)(current_time - game->last_time) / (float)game->frequency;
    game->last_time = current_time;

    if (frame_time > 0.25f) frame_time = 0.25f;

    game->accumulator += frame_time;
    
    while (game->accumulator >= FIXED_TIME_STEP) {
        game->delta_time = FIXED_TIME_STEP;
        game_update(game);
        game->accumulator -= FIXED_TIME_STEP;
    }

    game_draw(game);

    Uint64 end_time = SDL_GetPerformanceCounter();
    float frame_process_time = (float)(end_time - current_time) / (float)game->frequency;

    if (frame_process_time < TARGET_FRAME_TIME) {
        float sleep_time = TARGET_FRAME_TIME - frame_process_time;
        SDL_Delay((Uint32)(sleep_time * 1000.0f)); 
    }
}

void game_run(Game *game){
    if(game == NULL) return;
    game->is_running = true;

    if(game->state_manager != NULL) state_manager_push(game->state_manager, playing_state_create(), game);

    while(game->is_running){
        SDL_PumpEvents();
        keyboard_update(&game->keyboard);
        commands_update(&game->commands, &game->keyboard);
        game_loop(game);
    }
}