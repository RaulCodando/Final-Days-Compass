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
    
    bool result = init_entities(&game_entities);

    assert(result == true);
    assert(game_entities != NULL);

    vector_destroy(game_entities, NULL);
    printf("test_init_entities passed\n");
}

void test_add_entity(void) {
    Vector *game_entities = vector_create();
    Sprite *sprite = sprite_create("tests/assets/test_player_sprite.txt");
    Entity *entity = entity_create(PLAYER, sprite, NULL, 5.0f, 0.0f, 0.0f);
    
    bool result = add_entity(&game_entities, entity);
    
    assert(result == true);
    assert(game_entities != NULL);
    assert(game_entities->size == 1);

    Entity *player = (Entity*)vector_get(game_entities, 0);
    assert(player != NULL);
    entity_destroy(player);
    
    vector_destroy(game_entities, (destroy_data_func)entity_destroy);
    printf("test_add_entity passed\n");
}

void test_entity_manager(void) {
    test_init_entities();
    test_add_entity();
    printf("test_entity_manager passed\n");
}