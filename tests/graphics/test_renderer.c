#include "test_renderer.h"
#include "../../src/graphics/renderer.h"
#include "../../src/graphics/sprite.h"
#include "../../src/core/settings.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_renderer_create(){
    Renderer *renderer = renderer_create(10, 10);
    assert(renderer != NULL);
    assert(renderer->viewport_width == 10);
    assert(renderer->viewport_height == 10);
    assert(renderer->buffer != NULL);
    
    renderer_destroy(renderer);
    printf("test_renderer_create passed.\n");
}

void test_renderer_draw(){
    Renderer *renderer = renderer_create(10, 10);
    Sprite *sprite = sprite_create("tests/assets/test_sprite02.txt");

    assert(renderer != NULL);
    assert(sprite != NULL);

    renderer_draw(renderer, 5, 5, sprite);

    assert(renderer->buffer[5][5] == 'A');
    assert(renderer->buffer[5][6] == 'B');
    assert(renderer->buffer[6][5] == ' ');
    assert(renderer->buffer[6][6] == 'C');

    renderer_draw(renderer, 9, 9, sprite);

    renderer_destroy(renderer);
    sprite_destroy(sprite);

    printf("test_renderer_draw passed.\n");
}

void test_renderer_clear(){
    Renderer *renderer = renderer_create(10, 10);
    Sprite *sprite = sprite_create("tests/assets/test_sprite02.txt");

    assert(renderer != NULL);
    assert(sprite != NULL);

    renderer_draw(renderer, 5, 5, sprite);

    renderer_clear(renderer);

    for(int i = 0; i < renderer->viewport_height; i++){
        for(int j = 0; j < renderer->viewport_width; j++){
            assert(renderer->buffer[i][j] == BLANK_CHARACTER);
        }
    }

    renderer_destroy(renderer);
    sprite_destroy(sprite);

    printf("test_renderer_clear passed.\n");
}

void test_renderer_present(){
    Renderer *renderer = renderer_create(10, 10);
    Sprite *sprite = sprite_create("tests/assets/test_sprite02.txt");

    assert(renderer != NULL);
    assert(sprite != NULL);

    renderer_draw(renderer, 5, 5, sprite);

    renderer_present(renderer);

    renderer_destroy(renderer);
    sprite_destroy(sprite);

    printf("test_renderer_present passed.\n");
}

void test_renderer(){
    test_renderer_create();
    test_renderer_draw();
    test_renderer_clear();
    test_renderer_present();

    printf("All renderer tests passed.\n");
}