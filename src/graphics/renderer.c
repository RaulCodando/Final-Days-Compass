#include "renderer.h"
#include "sprite.h"
#include "../core/settings.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

Renderer *renderer_create(int width, int height){
    Renderer *renderer = (Renderer*) malloc(sizeof(Renderer));

    if(renderer == NULL){
        fprintf(stderr, "Error: memory allocation failed.\n");
        return NULL;
    }

    renderer->viewport_width = width;
    renderer->viewport_height = height;
    renderer->buffer = (char**) malloc(sizeof(char*)*height);

    if(renderer->buffer == NULL){
        fprintf(stderr, "Error: memory allocation failed.\n");
        free(renderer);
        return NULL;
    }

    for (size_t i = 0; i < height; i++){
        renderer->buffer[i] = (char*) malloc(sizeof(char)*width);
        if(renderer->buffer[i] == NULL){
            fprintf(stderr, "Error: memory allocation failed.\n");
            renderer_destroy(renderer);
            return NULL;
        }
    }
    renderer_clear(renderer);
    return renderer;
}

void renderer_clear(Renderer *renderer){
    for (size_t i = 0; i < renderer->viewport_height; i++){
        for (size_t j = 0; j < renderer->viewport_width; j++){
            renderer->buffer[i][j] = BLANK_CHARACTER;
        }
    }
}

void renderer_draw(Renderer *renderer, int x, int y, struct Sprite *sprite){
    for(int i = 0; i < sprite->height; i++){
        for(int j = 0; j < sprite->width; j++){
            int target_x = x + j;
            int target_y = y + i;

            if(target_x >= 0 && target_x < renderer->viewport_width && target_y >=0 && target_y < renderer->viewport_height){
                if(sprite->pixels[i * sprite->width + j] != BLANK_CHARACTER){
                    renderer->buffer[target_y][target_x] = sprite->pixels[i * sprite->width + j];
                }
            }
        }
    }
}

void renderer_present(Renderer *renderer){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0,0};
    SetConsoleCursorPosition(hConsole, coord);

    for(size_t i = 0; i < renderer->viewport_height; i++){
        printf("%.*s\n", renderer->viewport_width, renderer->buffer[i]);
    }
}

void renderer_destroy(Renderer *renderer){
    if (renderer == NULL) return;
    for (size_t i = 0; i < renderer->viewport_height; i++){
        free(renderer->buffer[i]);
    }
    free(renderer->buffer);
    free(renderer);
}