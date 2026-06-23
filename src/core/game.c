#include "game.h"
#include "../graphics/sprite.h"
#include "../world/map.h"
#include "settings.h"
#include <stdlib.h>

//Test variables
static float test_x = 0.0f;
static float test_y = 0.0f;
static float speed = 10.0f;
static float accumulator = 0.0f;
static Sprite *test_sprite = NULL;
static Map *test_map = NULL;

Game *game_create(void){
    Game *game = (Game*) malloc(sizeof(Game));
    if(game == NULL) return NULL;

    game->renderer = renderer_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(game->renderer == NULL){
        free(game);
        return NULL;
    }

    test_sprite = sprite_create("tests/assets/test_sprite03.txt");
    if(test_sprite == NULL){
        renderer_destroy(game->renderer);
        free(game);
        return NULL;
    }

    test_map = map_create_from_file("tests/assets/test_tile_map03.txt", 8);
    if(test_map == NULL){
        renderer_destroy(game->renderer);
        sprite_destroy(test_sprite);
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

    if (test_sprite != NULL) {
        sprite_destroy(test_sprite);
    }

    if (test_map != NULL) {
        map_destroy(test_map);
    }
    
    renderer_destroy(game->renderer);
    free(game);
}

void game_update(Game *game){
    if(!game) return;

    if (game->commands.quit_game.active) {
        game->is_running = false;
        return;
    }

    if (game->commands.move_left.active) {
        test_x -= 2 * speed * game->delta_time;
    }
    if (game->commands.move_right.active) {
        test_x += 2 * speed * game->delta_time;
    }
    if (game->commands.move_up.active) {
        test_y -= speed * game->delta_time;
    }
    if (game->commands.move_down.active) {
        test_y += speed * game->delta_time;
    }

    if(test_x >= SCREEN_WIDTH) test_x = 0.0f;
    if(test_x < 0) test_x = SCREEN_WIDTH - 1.0f;
    if(test_y >= SCREEN_HEIGHT) test_y = 0.0f;
    if(test_y < 0) test_y = SCREEN_HEIGHT - 1.0f;
}

void game_draw(Game *game){
    renderer_clear(game->renderer);

    if (test_map != NULL) {
        renderer_draw_map(game->renderer, 0, 0, test_map);
    }

    if (test_sprite != NULL) {
        renderer_draw(game->renderer, (int)test_x, (int)test_y, test_sprite);
    }

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