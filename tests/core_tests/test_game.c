#include "test_game.h"
#include "../../src/core/game.h"
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
    const char *sprite_paths[1] = {"tests/assets/test_player_sprite.txt"};
    ObjectIDs object_ids[1] = {PLAYER};
    Game *game = game_create();
    assert(game != NULL);
    assert(manage_entities_init(game, object_ids, sprite_paths, 1) == true);
    game_destroy(game);
    printf("test_manage_entities_init passed.\n");
}

void test_manage_entities_add(void){
    const char *sprite_paths[1] = {"tests/assets/test_player_sprite.txt"};
    ObjectIDs object_ids[1] = {PLAYER};
    Game *game = game_create();
    assert(game != NULL);
    assert(manage_entities_init(game, object_ids, sprite_paths, 1) == true);
    assert(manage_entities_add(game, PLAYER, 20, 1, 10.0f, 0.0f, 0.0f, "tests/assets/test_player_sprite.txt") == true);
    game_destroy(game);
    printf("test_manage_entities_add passed.\n");
}

void test_manage_entities_init_collider(void){
    const char *sprite_paths[1] = {"tests/assets/test_player_sprite.txt"};
    ObjectIDs object_ids[1] = {PLAYER};
    Game *game = game_create();
    assert(game != NULL);
    assert(manage_entities_init(game, object_ids, sprite_paths, 1) == true);
    assert(manage_entities_add(game, PLAYER, 20, 1, 10.0f, 0.0f, 0.0f, "tests/assets/test_player_sprite.txt") == true);
    assert(manage_entities_init_collider(game, PLAYER, 2.0f, 8.0f, 3.0f, 0.0f) == true);
    game_destroy(game);
    printf("test_manage_entities_init_collider passed.\n");
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
    const char *sprite_paths[2] = {"tests/assets/test_player_sprite.txt", 
                                   "tests/assets/test_entity_sprite.txt"};
    static char tile_ids[1] = {(char) 5};
    ObjectIDs object_ids[2] = {PLAYER, TEST_ENTITY};
    assert(game != NULL);

    if(manage_window_init(game, 0.0f, 0.0f, 0.25f) == false){
        game_destroy(game);
        assert(false);
    }

    if(manage_entities_init(game, object_ids, sprite_paths, 2) == false){
        game_destroy(game);
        assert(false);
    }

    if(manage_entities_add(game, PLAYER, 20, 1, 10.0f, 0.0f, 0.0f, "tests/assets/test_player_sprite.txt") == false){
        game_destroy(game);
        assert(false);
    }

    if(manage_entities_add(game, TEST_ENTITY, 20, 1, 10.0f, 16.0f, 0.0f, "tests/assets/test_entity_sprite.txt") == false){
        game_destroy(game);
        assert(false);
    }

    if(manage_entities_init_collider(game, PLAYER, 2.0f, 8.0f, 3.0f, 0.0f) == false){
        game_destroy(game);
        assert(false);
    }

    if(manage_entities_init_collider(game, TEST_ENTITY, 4.0f, 8.0f, 2.0f, 0.0f) == false){
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
    test_manage_entities_init_collider();
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