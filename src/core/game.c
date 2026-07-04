#include "game.h"
#include "../graphics/sprite.h"
#include "../objects/asset_manager.h"
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
    game->entity_count = 0;
    game->accumulator = 0.0f;
    game->is_running = false;
    
    return game;
}

void game_init_window(Game *game, float camera_x, float camera_y, float dead_zone_percentage){
    if(!game) return;
    
    game->camera = camera_create(camera_x, camera_y, dead_zone_percentage, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(game->camera == NULL){ 
        printf("Failed to create camera\n");
        return;
    }
    
    game->renderer = renderer_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(game->renderer == NULL){
        camera_destroy(game->camera);
        printf("Failed to create renderer\n");
        return;
    }
}

void game_destroy(Game *game){
    if(game == NULL) return;

    if (game->entities != NULL) entity_destroy(game->entities);
    if (game->map != NULL) map_destroy(game->map);
    if(game->solid_tile_ids.solid_tile_ids->tile_count > 0) solid_tile_ids_destroy(game->solid_tile_ids.solid_tile_ids);
    if (game->camera != NULL) camera_destroy(game->camera);
    if (game->asset_manager != NULL) asset_manager_destroy(game->asset_manager);
    if (game->renderer != NULL) renderer_destroy(game->renderer);
    free(game);
}

void game_update(Game *game){
    if(!game || !game->player) return;

    if (game->commands.quit_game.active) {
        game->is_running = false;
        return;
    }

    if (game->commands.move_left.active) {
        entity_move_and_collide(game->player, -2.0f * game->player->speed * game->delta_time, 0.0f, game->map, &game->solid_tile_ids, NULL, 0);
    }
    if (game->commands.move_right.active) {
        entity_move_and_collide(game->player, 2.0f * game->player->speed * game->delta_time, 0.0f, game->map, &game->solid_tile_ids, NULL, 0);
    }
    if (game->commands.move_up.active) {
        entity_move_and_collide(game->player, 0.0f, -game->player->speed * game->delta_time, game->map, &game->solid_tile_ids, NULL, 0);
    }
    if (game->commands.move_down.active) {
        entity_move_and_collide(game->player, 0.0f, game->player->speed * game->delta_time, game->map, &game->solid_tile_ids, NULL, 0);
    }

    int map_width_px = game->map->width * game->map->tile_size;
    int map_height_px = game->map->height * game->map->tile_size;

    if(game->player->x_pos >= (float)map_width_px) game->player->x_pos = 0.0f - game->player->base.sprite->width;
    if(game->player->x_pos + game->player->base.sprite->width < 0) game->player->x_pos = (float)map_width_px - 1.0f;
    if(game->player->y_pos >= (float)map_height_px) game->player->y_pos = 0.0f - game->player->base.sprite->height;
    if(game->player->y_pos + game->player->base.sprite->height < 0) game->player->y_pos = (float)map_height_px - 1.0f;

    camera_update(game->camera, game->player->x_pos, game->player->y_pos, game->player->base.sprite->width, game->player->base.sprite->height, map_width_px, map_height_px);
}

void game_draw(Game *game){
    if(!game || !game->player) return;

    renderer_clear(game->renderer);

    if (game->map != NULL) {
        renderer_draw_map(game->renderer, game->camera, game->map);
    }

    int player_screen_x = (int) floorf(game->player->x_pos - game->camera->x);
    int player_screen_y = (int) floorf(game->player->y_pos - game->camera->y);

    renderer_draw(game->renderer, player_screen_x, player_screen_y, game->player->base.sprite);

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