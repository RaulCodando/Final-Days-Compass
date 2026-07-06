#include "../../src/graphics/sprite.h"
#include "test_sprite.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <assert.h>

void test_sprite_create_blank(){
    Sprite *sprite = sprite_create_blank(7, 7);
    
    assert(sprite != NULL);
    assert(sprite->width == 7 && sprite->height == 7);
    assert(sprite->pixels != NULL);

    print_sprite(sprite);
    printf("test_sprite_create_blank passed successfully.\n");
    sprite_destroy(sprite);
}

void test_sprite_create(){
    Sprite *sprite = sprite_create("tests/assets/test_sprite01.txt");
    
    assert(sprite != NULL);
    assert(sprite->width == 7 && sprite->height == 7);
    assert(sprite->pixels != NULL);

    print_sprite(sprite);
    printf("test_sprite_create passed successfully.\n");
    sprite_destroy(sprite);
}

void test_sprite(){
    test_sprite_create_blank();
    test_sprite_create();
}