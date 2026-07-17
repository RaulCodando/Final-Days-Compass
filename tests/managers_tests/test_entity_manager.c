#include "test_entity_manager.h"
#include "../../src/managers/entity_manager.h"
#include "../../src/objects/asset_manager.h"
#include "../../src/objects/entity.h"
#include "../../src/graphics/sprite.h"
#include "../../src/utils/vector.h"
#include "../../src/entity_behaviors/player_behavior.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_init_entities(void) {
    Vector *game_entities = NULL;
    AssetManager *asset_manager = NULL;
    
    bool result = init_entities(&game_entities, &asset_manager, NULL, NULL, 0);

    assert(result == true);
    assert(game_entities != NULL);
    assert(asset_manager != NULL);

    vector_destroy(game_entities, NULL);
    asset_manager_destroy(asset_manager);
    printf("test_init_entities passed\n");
}

void test_add_entity(void) {
    Vector *game_entities = vector_create();
    AssetManager *asset_manager = asset_manager_create();
    int game_entity_count = 0;
    
    bool result = add_entity(&game_entities, &asset_manager, &game_entity_count, PLAYER, 100, 10, 5.0f, 0.0f, 0.0f, "tests/assets/test_player_sprite.txt");
    
    assert(result == true);
    assert(game_entities != NULL);
    assert(game_entities->size == 1);
    assert(game_entity_count == 1);

    Entity *player = (Entity*)vector_get(game_entities, 0);
    assert(player != NULL);
    entity_destroy(player);
    
    vector_destroy(game_entities, (destroy_data_func)entity_destroy);
    asset_manager_destroy(asset_manager);
    printf("test_add_entity passed\n");
}

void test_add_entity_behavior(void) {
    Vector *game_entities = vector_create();
    AssetManager *asset_manager = asset_manager_create();
    int game_entity_count = 0;
    
    add_entity(&game_entities, &asset_manager, &game_entity_count, PLAYER, 100, 10, 5.0f, 0.0f, 0.0f, "tests/assets/test_player_sprite.txt");
    
    bool result = add_entity_behavior(&game_entities, PLAYER, player_update);
    
    assert(result == true);
    assert(game_entity_count == 1);

    Entity *player = (Entity*)vector_get(game_entities, 0);
    assert(player != NULL);
    entity_destroy(player);
    
    vector_destroy(game_entities, (destroy_data_func)entity_destroy);
    asset_manager_destroy(asset_manager);
    printf("test_add_entity_behavior passed\n");
}

void test_init_entity_collider(void) {
    Vector *game_entities = vector_create();
    AssetManager *asset_manager = asset_manager_create();
    int game_entity_count = 0;
    
    add_entity(&game_entities, &asset_manager, &game_entity_count, PLAYER, 100, 10, 5.0f, 0.0f, 0.0f, "tests/assets/test_player_sprite.txt");
    
    bool result = init_entity_collider(&game_entities, PLAYER, 32.0f, 32.0f, 0.0f, 0.0f);
    
    assert(result == true);
    assert(game_entity_count == 1);

    Entity *player = (Entity*)vector_get(game_entities, 0);

    entity_destroy(player);
    vector_destroy(game_entities, (destroy_data_func)entity_destroy);
    asset_manager_destroy(asset_manager);
    printf("test_init_entity_collider passed\n");
}

void test_entity_manager(void) {
    test_init_entities();
    test_add_entity();
    test_add_entity_behavior();
    test_init_entity_collider();
    printf("test_entity_manager passed\n");
}