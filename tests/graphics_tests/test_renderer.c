#include "test_renderer.h"
#include "../../src/graphics/renderer.h"
#include "../../src/graphics/sprite.h"
#include "../../src/world/map.h"
#include "../../src/core/settings.h"
#include "../../src/graphics/camera.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Renderer *test_renderer_create(SDL_Window *window) {
    Renderer *renderer = renderer_create(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    assert(renderer != NULL);
    printf("  [PASS] test_renderer_create\n");
    return renderer;
}

void test_renderer_clear(Renderer *renderer) {
    assert(renderer != NULL);
    printf("  [PASS] test_renderer_clear\n");
    renderer_clear(renderer);
}

void test_renderer_draw(Renderer *renderer) {
    assert(renderer != NULL);
    Sprite *sprite = sprite_create(renderer->sdl_renderer, "refactoring_tests/assets/test_sprite.png");
    assert(sprite != NULL);
    renderer_draw(renderer, 0, 0, sprite);
    printf("  [PASS] test_renderer_draw\n");
    sprite_destroy(sprite);
}

void test_renderer_draw_tile(Renderer *renderer) {
    assert(renderer != NULL);
    SDL_Color color = {255, 255, 255, 255};
    TileSet *tileset = tileset_create(renderer->sdl_renderer, 16, 16, color);
    assert(tileset != NULL);
    renderer_draw_tile(renderer, 0, 0, 1, tileset);
    SDL_Delay(500);
    printf("  [PASS] test_renderer_draw_tile\n");
    tileset_destroy(tileset);
}

void test_renderer_draw_map(Renderer *renderer) {
    assert(renderer != NULL);
    SDL_Color color = {255, 255, 255, 255};
    Map *map = map_create_from_file(renderer->sdl_renderer, "refactoring_tests/assets/test_tile_map.txt", 16, color);
    assert(map != NULL);
    Camera *camera = camera_create(0.0f, 0.0f, 1.0f, 800, 600);
    assert(camera != NULL);
    renderer_draw_map(renderer, camera, map);
    printf("  [PASS] test_renderer_draw_map\n");
    camera_destroy(camera);

    SDL_Delay(500);
    map_destroy(map);
}

void test_renderer_present(Renderer *renderer) {
    assert(renderer != NULL);
    renderer_present(renderer);
    printf("  [PASS] test_renderer_present\n");
    SDL_Delay(3000);
}

void test_renderer() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Test Renderer", 800, 600, 0);
    assert(window != NULL);
    
    Renderer *renderer = test_renderer_create(window);
    
    test_renderer_clear(renderer);
    test_renderer_draw(renderer);
    test_renderer_draw_tile(renderer);
    test_renderer_draw_map(renderer);
    test_renderer_present(renderer);
    
    renderer_destroy(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}