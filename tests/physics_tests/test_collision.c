#include "test_collision.h"
#include "../../src/physics/collision.h"
#include "../../src/utils/vector.h"
#include "../../src/objects/entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define EPSILON 0.0001f
#define ASSERT_FLOAT_EQUAL(VALUE, EXPECTED) assert(fabs((VALUE) - (EXPECTED)) < EPSILON)

void test_collider_create(){
    Collider* collider = collider_create(0.0f, 0.0f, 1.0f, 1.0f);
    assert(collider != NULL);

    ASSERT_FLOAT_EQUAL(collider->x, 0.0f);
    ASSERT_FLOAT_EQUAL(collider->y, 0.0f);
    ASSERT_FLOAT_EQUAL(collider->width, 1.0f);
    ASSERT_FLOAT_EQUAL(collider->height, 1.0f);

    collider_destroy(collider);
    printf("Collider creation passed\n");
}

void test_solid_tile_ids_init(){
    SolidTileIDs solid_tile_ids;
    char tile_ids[] = {1, 2, 3};

    solid_tile_ids_init(&solid_tile_ids, tile_ids, 3);

    assert(solid_tile_ids.tile_count == 3);

    for(int i = 0; i < solid_tile_ids.tile_count; i++){
        assert(solid_tile_ids.solid_tile_ids[i] == tile_ids[i]);
    }

    solid_tile_ids_destroy(&solid_tile_ids);
    printf("Solid tile ids init passed\n");
}

void test_is_collider_overlapping(){
    Collider* collider_a = collider_create(0.0f, 0.0f, 2.0f, 2.0f);
    Collider* collider_b = collider_create(1.0f, 1.0f, 2.0f, 2.0f);
    Collider* collider_c = collider_create(3.0f, 3.0f, 2.0f, 2.0f);

    assert(is_collider_overlapping(collider_a, collider_b));
    assert(!is_collider_overlapping(collider_a, collider_c));

    collider_destroy(collider_a);
    collider_destroy(collider_b);
    collider_destroy(collider_c);
    printf("Is collider overlapping passed\n");
}

void test_is_tile_solid(){
    SolidTileIDs solid_tile_ids;
    char tile_ids[] = {1, 2, 3};
    solid_tile_ids_init(&solid_tile_ids, tile_ids, 3);
    assert(is_tile_solid(1, &solid_tile_ids));
    assert(is_tile_solid(2, &solid_tile_ids));
    assert(is_tile_solid(3, &solid_tile_ids));
    assert(!is_tile_solid(4, &solid_tile_ids));
    solid_tile_ids_destroy(&solid_tile_ids);
    printf("Is tile solid passed\n");
}

void test_resolve_map_collision(){
    Map* map = map_create_from_file("tests/assets/test_tile_map01.txt", 8);
    Collider* collider = collider_create(0.0f, 0.0f, 8.0f, 8.0f);
    float vel_x = 1.0f;
    float vel_y = 1.0f;
    SolidTileIDs solid_tile_ids;
    char tile_ids[] = {1};
    solid_tile_ids_init(&solid_tile_ids, tile_ids, 1);

    resolve_map_collision(collider, &vel_x, &vel_y, map, &solid_tile_ids);
    ASSERT_FLOAT_EQUAL(vel_x, 0.0f);
    ASSERT_FLOAT_EQUAL(vel_y, 1.0f);
    ASSERT_FLOAT_EQUAL(collider->x, 0.0f);
    ASSERT_FLOAT_EQUAL(collider->y, 1.0f);

    collider_destroy(collider);
    solid_tile_ids_destroy(&solid_tile_ids);
    map_destroy(map);
    printf("Resolve map collision passed\n");
}

void test_resolve_custom_collision(){
    Collider* collider_a = collider_create(0.0f, 0.0f, 1.0f, 1.0f);
    Collider* collider_b = collider_create(1.0f, 0.0f, 1.0f, 2.0f);
    Vector* colliders = vector_create();
    vector_push(colliders, collider_b);
    float vel_x = 1.0f;
    float vel_y = 1.0f;

    resolve_custom_collision(collider_a, &vel_x, &vel_y, colliders);
    ASSERT_FLOAT_EQUAL(vel_x, 0.0f);
    ASSERT_FLOAT_EQUAL(vel_y, 1.0f);
    ASSERT_FLOAT_EQUAL(collider_a->x, 0.0f);
    ASSERT_FLOAT_EQUAL(collider_a->y, 1.0f);

    collider_destroy(collider_a);
    collider_destroy(collider_b);
    printf("Resolve custom collision passed\n");
}

void test_resolve_entity_collision(){
    Sprite* sprite = sprite_create("tests/assets/test_entity_sprite.txt");
    Entity* entity_a = entity_create(1, sprite, 10, 1, 1.0f, 0.0f, 0.0f);
    Entity* entity_b = entity_create(1, sprite, 10, 1, 1.0f, 1.0f, 0.0f);
    entity_init_collider(entity_a, 1.0f, 1.0f, 0.0f, 0.0f);
    entity_init_collider(entity_b, 1.0f, 2.0f, 0.0f, 0.0f);
    Vector* entities = vector_create();
    vector_push(entities, entity_b);
    float vel_x = 1.0f;
    float vel_y = 1.0f;

    resolve_entity_collision(entity_a, &vel_x, &vel_y, entities);
    ASSERT_FLOAT_EQUAL(vel_x, 0.0f);
    ASSERT_FLOAT_EQUAL(vel_y, 1.0f);
    ASSERT_FLOAT_EQUAL(entity_a->collider->x, 0.0f);
    ASSERT_FLOAT_EQUAL(entity_a->collider->y, 1.0f);

    entity_destroy(entity_a);
    entity_destroy(entity_b);
    vector_destroy(entities);
    printf("Resolve entity collision passed\n");
}

void test_collision(){
    test_collider_create();
    test_solid_tile_ids_init();
    test_is_collider_overlapping();
    test_is_tile_solid();
    test_resolve_map_collision();
    test_resolve_custom_collision();
    test_resolve_entity_collision();
}