#include "game.h"
#include "settings.h"
#include "../graphics/sprite.h"
#include <stdlib.h>

//Test variables
static float test_x = 0.0f;
static float test_y = 0.0f;
static float speed = 10.0f;
static Sprite *test_sprite = NULL;

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
        test_x -= 0.05f;
    }
    if (game->commands.move_right.active) {
        test_x += 0.05f;
    }
    if (game->commands.move_up.active) {
        test_y -= 0.05f;
    }
    if (game->commands.move_down.active) {
        test_y += 0.05f;
    }

    if(test_x >= SCREEN_WIDTH) test_x = 0.0f;
    if(test_x < 0) test_x = SCREEN_WIDTH - 1.0f;
    if(test_y >= SCREEN_HEIGHT) test_y = 0.0f;
    if(test_y < 0) test_y = SCREEN_HEIGHT - 1.0f;
}

void game_draw(Game *game){
    renderer_clear(game->renderer);

    if (test_sprite != NULL) {
        renderer_draw(game->renderer, (int)test_x, (int)test_y, test_sprite);
    }

    renderer_present(game->renderer);
}

void game_loop(Game *game){
    LARGE_INTEGER current_time;
    QueryPerformanceCounter(&current_time);

    long long elapsed_ticks = current_time.QuadPart - game->last_time.QuadPart;
    game->delta_time = (float) elapsed_ticks / (float) game->frequency.QuadPart;

    game->last_time = current_time;

    game_update(game);
    game_draw(game);
}

void game_run(Game *game){
    if(game == NULL) return;
    while(game->is_running){
        keyboard_update(&game->keyboard);
        commands_update(&game->commands, &game->keyboard);
        game_loop(game);
    }
}