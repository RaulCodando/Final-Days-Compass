#include "game.h"
#include "../graphics/sprite.h"
#include "../objects/asset_manager.h"
#include "../objects/entity.h"
#include "../world/map.h"
#include "../physics/collision.h"
#include "settings.h"
#include <stdlib.h>

static float accumulator = 0.0f;
static Entity *player = NULL;
static Map *test_map = NULL;
static SolidTileIDs solid_tile_ids;
static char ids[] = {(char) 5};

Game *game_create(void){
    Game *game = (Game*) malloc(sizeof(Game));
    if(game == NULL) return NULL;

    game->renderer = renderer_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(game->renderer == NULL){
        free(game);
        return NULL;
    }

    game->camera = camera_create(0.0f, 0.0f, 0.25f, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(game->camera == NULL){
        renderer_destroy(game->renderer);
        free(game);
        return NULL;
    }

    game->asset_manager = asset_manager_create();
    if(game->asset_manager == NULL){
        camera_destroy(game->camera);
        renderer_destroy(game->renderer);
        free(game);
        return NULL;
    }

    Sprite *player_sprite = asset_manager_get(game->asset_manager, PLAYER, "tests/assets/test_player_sprite.txt");
    if(player_sprite == NULL){
        camera_destroy(game->camera);
        renderer_destroy(game->renderer);
        asset_manager_destroy(game->asset_manager);
        free(game);
        return NULL;
    }

    player = entity_create(PLAYER, player_sprite, 20, 1, 10.0f, 0.0f, 0.0f);
    if(player == NULL){
        camera_destroy(game->camera);
        renderer_destroy(game->renderer);
        asset_manager_destroy(game->asset_manager);
        free(game);
        return NULL;
    }

    solid_tile_ids_init(&solid_tile_ids, ids, 1);

    entity_init_collider(player, 2.0f, 8.0f, 4.0f, 0.0f);
    if(player->collider == NULL){
        camera_destroy(game->camera);
        renderer_destroy(game->renderer);
        asset_manager_destroy(game->asset_manager);
        entity_destroy(player);
        solid_tile_ids_destroy(&solid_tile_ids);
        free(game);
        return NULL;
    }

    test_map = map_create_from_file("tests/assets/test_tile_map03.txt", 8);
    if(test_map == NULL){
        camera_destroy(game->camera);
        renderer_destroy(game->renderer);
        asset_manager_destroy(game->asset_manager);
        entity_destroy(player);
        solid_tile_ids_destroy(&solid_tile_ids);
        free(game);
        return NULL;
    }

    keyboard_init(&game->keyboard);
    commands_init(&game->commands);

    game->is_running = true;

    QueryPerformanceFrequency(&game->frequency);
    QueryPerformanceCounter(&game->last_time);

    return game;
}

void game_destroy(Game *game){
    if(game == NULL) return;

    if (player != NULL) entity_destroy(player);
    if (test_map != NULL) map_destroy(test_map);
    solid_tile_ids_destroy(&solid_tile_ids);

    if (game->camera != NULL) camera_destroy(game->camera);
    if (game->asset_manager != NULL) asset_manager_destroy(game->asset_manager);
    if (game->renderer != NULL) renderer_destroy(game->renderer);
    free(game);
}

void game_update(Game *game){
    if(!game || !player) return;

    if (game->commands.quit_game.active) {
        game->is_running = false;
        return;
    }

    if (game->commands.move_left.active) {
        entity_move_and_collide(player, -2.0f * player->speed * game->delta_time, 0.0f, test_map, &solid_tile_ids, NULL, 0);
    }
    if (game->commands.move_right.active) {
        entity_move_and_collide(player, 2.0f * player->speed * game->delta_time, 0.0f, test_map, &solid_tile_ids, NULL, 0);
    }
    if (game->commands.move_up.active) {
        entity_move_and_collide(player, 0.0f, -player->speed * game->delta_time, test_map, &solid_tile_ids, NULL, 0);
    }
    if (game->commands.move_down.active) {
        entity_move_and_collide(player, 0.0f, player->speed * game->delta_time, test_map, &solid_tile_ids, NULL, 0);
    }

    int map_width_px = test_map->width * test_map->tile_size;
    int map_height_px = test_map->height * test_map->tile_size;

    if(player->x_pos >= (float)map_width_px) player->x_pos = 0.0f - player->base.sprite->width;
    if(player->x_pos + player->base.sprite->width < 0) player->x_pos = (float)map_width_px - 1.0f;
    if(player->y_pos >= (float)map_height_px) player->y_pos = 0.0f - player->base.sprite->height;
    if(player->y_pos + player->base.sprite->height < 0) player->y_pos = (float)map_height_px - 1.0f;

    camera_update(game->camera, player->x_pos, player->y_pos, player->base.sprite->width, player->base.sprite->height, map_width_px, map_height_px);
}

void game_draw(Game *game){
    if(!game || !player) return;

    renderer_clear(game->renderer);

    if (test_map != NULL) {
        renderer_draw_map(game->renderer, game->camera, test_map);
    }

    int player_screen_x = (int)(player->x_pos - game->camera->x);
    int player_screen_y = (int)(player->y_pos - game->camera->y);
    int collider_screen_x = (int)(player->collider->x - game->camera->x);
    int collider_screen_y = (int)(player->collider->y - game->camera->y);

    renderer_draw(game->renderer, player_screen_x, player_screen_y, player->base.sprite);
    renderer_draw_debug_collider(game->renderer, player->collider, collider_screen_x, collider_screen_y);

    renderer_present(game->renderer);
}

void game_loop(Game *game){
    LARGE_INTEGER current_time;
    QueryPerformanceCounter(&current_time);

    long long elapsed_ticks = current_time.QuadPart - game->last_time.QuadPart;
    float frame_time = (float) elapsed_ticks / (float) game->frequency.QuadPart;
    game->last_time = current_time;

    accumulator += frame_time;
    
    while (accumulator >= FIXED_TIME_STEP) {
        game->delta_time = FIXED_TIME_STEP;
        game_update(game);
        accumulator -= FIXED_TIME_STEP;
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
    while(game->is_running){
        keyboard_update(&game->keyboard);
        commands_update(&game->commands, &game->keyboard);
        game_loop(game);
    }
}