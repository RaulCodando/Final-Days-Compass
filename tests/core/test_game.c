#include "test_game.h"
#include "../../src/core/game.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_game_create(void){
    Game *game = game_create();
    assert(game != NULL);
    assert(game->is_running == true);
    assert(game->renderer != NULL);
    game_destroy(game);
    printf("test_game_create passed.\n");
}

void test_game_update(void){
    Game *game = game_create();
    assert(game != NULL);
    game_update(game);
    game_destroy(game);
    printf("test_game_update passed.\n");
}

void test_game_draw(void){
    Game *game = game_create();
    assert(game != NULL);
    game_draw(game);
    game_destroy(game);
    printf("test_game_draw passed.\n");
}

void test_game_loop(void){
    Game *game = game_create();
    assert(game != NULL);
    game_loop(game);
    game_destroy(game);
    printf("test_game_loop passed.\n");
}

void test_game_run(void){
    Game *game = game_create();
    assert(game != NULL);
    game_run(game);
    game_destroy(game);
    printf("test_game_run passed.\n");
}

void test_game(void){
    test_game_create();
    test_game_update();
    test_game_draw();
    test_game_loop();
    test_game_run();
    system("cls");
}