#include "game.h"
#include "../graphics/sprite.h"
#include "../objects/asset_manager.h"
#include "../managers/window_manager.h"
#include "../managers/entity_manager.h"
#include "../managers/world_manager.h"
#include "settings.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Game *game_create(void){
    Game *game = (Game*) malloc(sizeof(Game));
    if(game == NULL) return NULL;

    keyboard_init(&game->keyboard);
    commands_init(&game->commands);
    QueryPerformanceFrequency(&game->frequency);
    QueryPerformanceCounter(&game->last_time);

    game->camera = NULL;
    game->entities = NULL;
    game->map = NULL;
    game->renderer = NULL;
    game->asset_manager = NULL;
    game->solid_tile_ids.solid_tile_ids = NULL;
    game->custom_colliders = NULL;
    game->solid_tile_ids.tile_count = 0;
    game->entity_count = 0;
    game->delta_time = 0.0f;
    game->accumulator = 0.0f;
    game->is_running = false;
    
    return game;
}

bool manage_window_init(Game *game, float camera_x, float camera_y, float dead_zone_percentage){
    if(game == NULL) return false;
    
    return init_window(&game->camera, &game->renderer, camera_x, camera_y, dead_zone_percentage);
}

bool manage_entities_init(Game *game, ObjectIDs *object_ids, const char **sprite_paths, int sprite_count){
    if(game == NULL) return false;
    
    return init_entities(&game->entities, &game->asset_manager, object_ids, sprite_paths, sprite_count);
}

bool manage_entities_add(Game *game, ObjectIDs id, int health, int standard_attack, float speed, float x_pos, float y_pos, const char *sprite_path){
    if(game == NULL) return false;
    
    return add_entity(&game->entities, &game->asset_manager, &game->entity_count, id, health, standard_attack, speed, x_pos, y_pos, sprite_path);
}

bool manage_entities_init_collider(Game *game, ObjectIDs id, float collider_width, float collider_height, float offset_x, float offset_y){
    if(game == NULL) return false;
    
    return init_entity_collider(&game->entities, id, collider_width, collider_height, offset_x, offset_y);
}

bool manage_world_init(Game *game, const char *map_file, int tile_size, char *tile_ids, int tile_count){
    if(game == NULL) return false;
    
    return init_world(&game->map, &game->solid_tile_ids, map_file, tile_size, tile_ids, tile_count);
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

    if (game->entities != NULL) {
        for(size_t i = 0; i < game->entities->size; i++){
            entity_destroy((Entity*)vector_get(game->entities, i));
        }
        vector_destroy(game->entities);
    }
    if (game->custom_colliders != NULL) {
        for(size_t i = 0; i < game->custom_colliders->size; i++){
            collider_destroy((Collider*)vector_get(game->custom_colliders, i));
        }
        vector_destroy(game->custom_colliders);
    }
    if (game->map != NULL) map_destroy(game->map);
    if (game->camera != NULL) camera_destroy(game->camera);
    if (game->asset_manager != NULL) asset_manager_destroy(game->asset_manager);
    if (game->renderer != NULL) renderer_destroy(game->renderer);

    solid_tile_ids_destroy(&game->solid_tile_ids);

    free(game);
}

void game_update(Game *game){
    if(!game || !game->entities) return;

    Entity *player = NULL;
    for (size_t i = 0; i < game->entities->size; i++) {
        Entity *entity = (Entity *)vector_get(game->entities, i);
        if(entity == NULL) continue;
        entity->vel_x = 0.0f;
        entity->vel_y = 0.0f;
        if(entity->base.id == PLAYER){
            player = entity;
        }
    }

    if(player == NULL) return;

    if (game->commands.quit_game.active) {
        game->is_running = false;
        return;
    }

    if (game->commands.move_left.active) player->vel_x = -2.0f * player->speed * game->delta_time;
    if (game->commands.move_right.active) player->vel_x = 2.0f * player->speed * game->delta_time;
    if (game->commands.move_up.active) player->vel_y = -1.0f * player->speed * game->delta_time;
    if (game->commands.move_down.active) player->vel_y = 1.0f * player->speed * game->delta_time;
    
    entity_move_and_collide(player, game->map, &game->solid_tile_ids, game->custom_colliders, game->entities);

    int map_width_px = game->map->width * game->map->tile_size;
    int map_height_px = game->map->height * game->map->tile_size;

    if(player->x_pos >= (float)map_width_px) player->x_pos = 0.0f - player->base.sprite->width;
    if(player->x_pos + player->base.sprite->width < 0) player->x_pos = (float)map_width_px - 1.0f;
    if(player->y_pos >= (float)map_height_px) player->y_pos = 0.0f - player->base.sprite->height;
    if(player->y_pos + player->base.sprite->height < 0) player->y_pos = (float)map_height_px - 1.0f;

    camera_update(game->camera, player->x_pos, player->y_pos, player->base.sprite->width, player->base.sprite->height, map_width_px, map_height_px);
}

void game_draw(Game *game){
    if(!game || !game->entities) return;

    renderer_clear(game->renderer);

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

    renderer_present(game->renderer);
}

void game_loop(Game *game){
    LARGE_INTEGER current_time;
    QueryPerformanceCounter(&current_time);

    long long elapsed_ticks = current_time.QuadPart - game->last_time.QuadPart;
    float frame_time = (float) elapsed_ticks / (float) game->frequency.QuadPart;
    game->last_time = current_time;

    game->accumulator += frame_time;
    
    while (game->accumulator >= FIXED_TIME_STEP) {
        game->delta_time = FIXED_TIME_STEP;
        game_update(game);
        game->accumulator -= FIXED_TIME_STEP;
    }

    game_draw(game);

    LARGE_INTEGER end_time;
    QueryPerformanceCounter(&end_time);

    float frame_process_time = (float)(end_time.QuadPart - current_time.QuadPart) / (float)game->frequency.QuadPart;
    if (frame_process_time < TARGET_FRAME_TIME) {
        float sleep_time = TARGET_FRAME_TIME - frame_process_time;
        Sleep((DWORD)(sleep_time * 1000.0f)); 
    }
}

void game_run(Game *game){
    if(game == NULL) return;

    game->is_running = true;

    while(game->is_running){
        keyboard_update(&game->keyboard);
        commands_update(&game->commands, &game->keyboard);
        game_loop(game);
    }
}