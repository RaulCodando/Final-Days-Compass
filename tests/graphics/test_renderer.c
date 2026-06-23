#include "test_renderer.h"
#include "../../src/graphics/renderer.h"
#include "../../src/graphics/sprite.h"
#include "../../src/world/map.h"
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

    assert(renderer->buffer[5 * renderer->viewport_width + 5].Char.AsciiChar == 'A');
    assert(renderer->buffer[5 * renderer->viewport_width + 6].Char.AsciiChar == 'B');
    assert(renderer->buffer[6 * renderer->viewport_width + 5].Char.AsciiChar == ' ');
    assert(renderer->buffer[6 * renderer->viewport_width + 6].Char.AsciiChar == 'C');

    renderer_draw(renderer, 9, 9, sprite);

    renderer_destroy(renderer);
    sprite_destroy(sprite);

    printf("test_renderer_draw passed.\n");
}

void test_renderer_draw_tile(){
    Renderer *renderer = renderer_create(10, 10);
    TileSet *tileset = tileset_create(2, 2);

    assert(renderer != NULL);
    assert(tileset != NULL);

    renderer_draw_tile(renderer, 5, 5, TEST_TILE03, tileset);

    assert(renderer->buffer[5 * renderer->viewport_width + 5].Char.AsciiChar == 'A');
    assert(renderer->buffer[5 * renderer->viewport_width + 6].Char.AsciiChar == 'B');
    assert(renderer->buffer[6 * renderer->viewport_width + 5].Char.AsciiChar == 'C');
    assert(renderer->buffer[6 * renderer->viewport_width + 6].Char.AsciiChar == 'D');

    renderer_destroy(renderer);
    tileset_destroy(tileset);

    printf("test_renderer_draw_tile passed.\n");
}

void test_renderer_draw_map(){
    Renderer *renderer = renderer_create(16, 16);
    Map *map = map_create_from_file("tests/assets/test_tile_map02.txt", 4);

    assert(renderer != NULL);
    assert(map != NULL);

    renderer_draw_map(renderer, 0, 0, map);

    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            printf("%c", renderer->buffer[i * renderer->viewport_width + j].Char.AsciiChar);
        }
        printf("\n");
    }

    renderer_destroy(renderer);
    map_destroy(map);

    printf("test_renderer_draw_map passed.\n");
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
            int index = i * renderer->viewport_width + j;
            assert(renderer->buffer[index].Char.AsciiChar == BLANK_CHARACTER);
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
    test_renderer_draw_tile();
    test_renderer_clear();
    test_renderer_draw_map();

    printf("\nMap drawing test completed. Proceed to the next test? (y/n): ");
    char response;
    scanf(" %c", &response);
    if(response != 'y' && response != 'Y'){
        exit(0);
    }
    system("cls");
    test_renderer_present();

    printf("End of tests in 2 seconds...\n");
    Sleep(2000);
    system("cls");

    printf("All renderer tests passed.\n");
}