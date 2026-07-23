#include "test_game.h"
#include "../../src/core/game.h"
#include "../../src/entity_behaviors/player_behavior.h"
#include "../../src/entity_behaviors/test_entity_behavior.h"
#include "../../src/entities/player.h"
#include "../../src/entities/dummy_entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>

void test_game_create(void){
    Game *game = game_create();
    assert(game != NULL);
    game_destroy(game);
    printf("test_game_create passed.\n");
}

void test_manage_window_init(void){
    Game *game = game_create();
    assert(game != NULL);
    assert(manage_window_init(game, 0.0f, 0.0f, 0.25f) == true);
    game_destroy(game);
    printf("test_manage_window_init passed.\n");
}

void test_manage_entities_init(void){
    Game *game = game_create();
    assert(game != NULL);
    assert(manage_entities_init(game) == true);
    game_destroy(game);
    printf("test_manage_entities_init passed.\n");
}

void test_manage_entities_add(void){
    Game *game = game_create();
    assert(game != NULL);
    assert(manage_entities_init(game) == true);
    Entity *test_entity = entity_create(TEST_ENTITY, NULL, NULL, 10.0f, 0.0f, 0.0f);
    assert(manage_entities_add(game, test_entity) == true);
    game_destroy(game);
    printf("test_manage_entities_add passed.\n");
}

void test_manage_world_init(void){
    char tile_ids[1] = {(char) 5};
    Game *game = game_create();
    assert(game != NULL);
    assert(manage_world_init(game, "tests/assets/test_tile_map03.txt", 8, tile_ids, 1) == true);
    game_destroy(game);
    printf("test_manage_world_init passed.\n");
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
    system("cls");
    printf("test_game_draw passed.\n");
}

void test_game_loop(void){
    Game *game = game_create();
    assert(game != NULL);
    game_loop(game);
    game_destroy(game);
    system("cls");
    printf("test_game_loop passed.\n");
}

void test_game_run(void){
    Game *game = game_create();
    assert(game != NULL);
    static char tile_ids[1] = {(char) 5};

    if(manage_window_init(game, 0.0f, 0.0f, 0.25f) == false){
        game_destroy(game);
        assert(false);
    }

    if(manage_entities_init(game) == false){
        game_destroy(game);
        assert(false);
    }

    if(player_spawn(game, 0.0f, 0.0f) == false){
        game_destroy(game);
        assert(false);
    }

    if(test_entity_spawn(game, 0.0f, 28.0f) == false){
        game_destroy(game);
        assert(false);
    }

    if(manage_world_init(game, "tests/assets/test_tile_map03.txt", 8, tile_ids, 1) == false){
        game_destroy(game);
        assert(false);
    }

    if(manage_world_colliders_init(game) == false){
        game_destroy(game);
        assert(false);
    }

    if(manage_world_colliders_add(game, 24.0f, 16.0f, 16.0f, 1.0f) == false){
        game_destroy(game);
        assert(false);
    }

    game_run(game);
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    game_destroy(game);
    system("cls");
    printf("test_game_run passed.\n");
}

void test_game(void){
    char response;

    test_game_create();
    test_manage_window_init();
    test_manage_entities_init();
    test_manage_entities_add();
    test_manage_world_init();
    test_game_update();
    
    printf("Do you want to continue with the test_game_draw? (y/n): ");
    scanf(" %c", &response);
    fflush(stdout);

    if(response == 'y' || response == 'Y') {
        test_game_draw();
    }

    printf("Do you want to continue with the test_game_loop? (y/n): ");
    scanf(" %c", &response);
    fflush(stdout);

    if(response == 'y' || response == 'Y') {
        test_game_loop();
    }

    printf("Do you want to continue with the test_game_run? (y/n): ");
    scanf(" %c", &response);
    fflush(stdout);

    if(response == 'y' || response == 'Y') {
        test_game_run();
    }
}