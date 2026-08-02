#include "test_refactored_sprite.h"
#include "../../src/graphics/sprite.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_sprite_create_blank(SDL_Renderer *renderer) {
    SDL_Color red = {255, 0, 0, 255};
    Sprite *sprite = sprite_create_blank(renderer, 16, 16, red);

    assert(sprite != NULL);
    assert(sprite->width == 16.0f && sprite->height == 16.0f);
    assert(sprite->texture != NULL);

    SDL_FRect dst_rect = {
        .x = 350.0f,
        .y = 250.0f,
        .w = sprite->width * 5.0f,
        .h = sprite->height * 5.0f
    };

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, sprite->texture, NULL, &dst_rect);
    SDL_RenderPresent(renderer);
    
    SDL_Delay(1000);
    sprite_destroy(sprite);

    printf("  [PASS] test_sprite_create_blank\n");
}

void test_sprite_create(SDL_Renderer *renderer) {
    Sprite *sprite = sprite_create(renderer, "refactoring_tests/assets/test_sprite.png");
    assert(sprite != NULL);
    assert(sprite->width > 0.0f && sprite->height > 0.0f);
    assert(sprite->texture != NULL);

    SDL_FRect dst_rect = {
        .x = 350.0f,
        .y = 250.0f,
        .w = sprite->width * 5.0f,
        .h = sprite->height * 5.0f
    };

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, sprite->texture, NULL, &dst_rect);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000);
    sprite_destroy(sprite);

    printf("  [PASS] test_sprite_create\n");
}

void test_sprite(void) {
    printf("\n=== Running Sprite Tests ===\n");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erro ao inicializar SDL: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *window = SDL_CreateWindow("Test Suite - Refactored Sprite", 800, 600, 0);
    if (!window) {
        fprintf(stderr, "Erro ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        fprintf(stderr, "Erro ao criar renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    test_sprite_create_blank(renderer);
    test_sprite_create(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("=== Sprite Tests Completed Successfully ===\n");
}