#include "test_tiles.h"
#include "../../src/world/tiles.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_tileset_create(){
    TileSet *tileset = tileset_create(8, 8);
    assert(tileset != NULL);
    assert(tileset->sprites[0] != NULL);
    assert(tileset->sprites[1] != NULL);
    
    tileset_destroy(tileset);
    printf("test_tileset_create passed successfully.\n");
}

void test_tileset_get_sprite(){
    TileSet *tileset = tileset_create(8, 8);
    assert(tileset != NULL);

    Sprite *expected_sprite = tileset->sprites[1]; 
    
    assert(expected_sprite != NULL);
    assert(tileset_get_sprite(tileset, TEST_TILE01) == expected_sprite);
    assert(tileset_get_sprite(tileset, TILE_COUNT) == NULL);
    assert(tileset_get_sprite(tileset, -1) == NULL);
    
    tileset_destroy(tileset); 
    
    printf("test_tileset_get_sprite passed successfully.\n");
}

void test_tileset(){
    test_tileset_create();
    test_tileset_get_sprite();
    printf("All world tileset tests passed flawlessly!\n");
}