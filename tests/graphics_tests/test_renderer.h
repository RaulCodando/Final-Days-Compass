#ifndef TEST_RENDERER_H
#define TEST_RENDERER_H

#include <SDL3/SDL.h>
#include "../../src/graphics/renderer.h"

Renderer *test_renderer_create(SDL_Window *window);
void test_renderer_clear(Renderer *renderer);
void test_renderer_draw(Renderer *renderer);
void test_renderer_draw_tile(Renderer *renderer);
void test_renderer_draw_map(Renderer *renderer);
void test_renderer_present(Renderer *renderer);
void test_renderer();

#endif //TEST_RENDERER_H