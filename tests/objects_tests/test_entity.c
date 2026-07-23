#include "test_entity.h"
#include "../../src/objects/entity.h"
#include "../../src/utils/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define EPSILON 0.0001f
#define ASSERT_FLOAT_EQUAL(VALUE, EXPECTED) assert(fabs((VALUE) - (EXPECTED)) < EPSILON)

void print_entity(Entity *entity){
    int height = entity->base.sprite->height;
    int width = entity->base.sprite->width;
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printf("%c", entity->base.sprite->pixels[i * width + j]);
        }
        printf("\n");
    }

    printf("Entity ID: %d\n", entity->base.id);
    printf("Entity Speed: %f\n", entity->speed);
    printf("Entity X Position: %f\n", entity->x_pos);
    printf("Entity Y Position: %f\n", entity->y_pos);
}

void test_entity_create(){
    Sprite *sprite = sprite_create("tests/assets/test_sprite04.txt");
    assert(sprite != NULL);

    Entity *entity = entity_create(PLAYER, sprite, NULL, 1.0f, 0.0f, 0.0f);
    assert(entity != NULL);

    print_entity(entity);
    printf("test_entity_create: PASSED\n");
    entity_destroy(entity);
    sprite_destroy(sprite);
}

void test_entity_init_collider(){
    Sprite *sprite = sprite_create("tests/assets/test_sprite04.txt");
    assert(sprite != NULL);

    Entity *entity = entity_create(PLAYER, sprite, NULL, 1.0f, 0.0f, 0.0f);
    assert(entity != NULL);

    entity_init_collider(entity, 1.0f, 1.0f, 1.0f, 1.0f);
    assert(entity->collider != NULL);
    assert(entity->collider->x == entity->x_pos + 1.0f);
    assert(entity->collider->y == entity->y_pos + 1.0f);
    assert(entity->collider->width == 1.0f);
    assert(entity->collider->height == 1.0f);
    assert(entity->offset_x == 1.0f);
    assert(entity->offset_y == 1.0f);

    print_entity(entity);
    printf("test_entity_init_collider: PASSED\n");
    entity_destroy(entity);
    sprite_destroy(sprite);
}

void test_entity_move_and_collide(){
    Map* map = map_create_from_file("tests/assets/test_tile_map04.txt", 8);
    assert(map != NULL);
    
    Sprite* sprite = sprite_create("tests/assets/test_sprite04.txt");
    assert(sprite != NULL);

    Entity* entity = entity_create(PLAYER, sprite, NULL, 1.0f, 0.0f, 0.0f);
    assert(entity != NULL);

    Vector* entities = vector_create();

    entity_init_collider(entity, 1.0f, 1.0f, 1.0f, 1.0f);
    assert(entity->collider != NULL);

    Collider collider = { .x = 2.0f, .y = 1.0f, .width = 1.0f, .height = 2.0f };

    Vector *colliders = vector_create();
    vector_push(colliders, &collider);

    SolidTileIDs solid_tile_ids;
    char tile_ids[] = {1};
    solid_tile_ids_init(&solid_tile_ids, tile_ids, 1);

    entity->vel_x = entity->speed;
    entity->vel_y = entity->speed;

    entity_move_and_collide(entity, map, &solid_tile_ids, colliders, entities);
    
    ASSERT_FLOAT_EQUAL(entity->x_pos, 0.0f);
    ASSERT_FLOAT_EQUAL(entity->y_pos, 1.0f);

    ASSERT_FLOAT_EQUAL(entity->collider->x, 1.0f);
    ASSERT_FLOAT_EQUAL(entity->collider->y, 2.0f);

    solid_tile_ids_destroy(&solid_tile_ids);
    
    print_entity(entity);
    printf("test_entity_move_and_collide: PASSED\n");
    entity_destroy(entity);
    sprite_destroy(sprite);
    map_destroy(map);
}

void test_entity(){
    test_entity_create();
    test_entity_init_collider();
    test_entity_move_and_collide();
    printf("test_entity: PASSED\n");
}