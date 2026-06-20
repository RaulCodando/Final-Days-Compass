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
    renderer->buffer = (CHAR_INFO*) malloc(sizeof(CHAR_INFO) * width * height);

    if(renderer->buffer == NULL){
        fprintf(stderr, "Error: memory allocation failed.\n");
        free(renderer);
        return NULL;
    }

    renderer_clear(renderer);
    return renderer;
}

void renderer_clear(Renderer *renderer){
    int total_pixels = renderer->viewport_width * renderer->viewport_height;
    for (int i = 0; i < total_pixels; i++){
        renderer->buffer[i].Char.AsciiChar = BLANK_CHARACTER;
        renderer->buffer[i].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED; // Branco padrão
    }
}

void renderer_draw(Renderer *renderer, int x, int y, struct Sprite *sprite){
    for(int i = 0; i < sprite->height; i++){
        for(int j = 0; j < sprite->width; j++){
            int target_x = x + j;
            int target_y = y + i;

            if(target_x >= 0 && target_x < renderer->viewport_width && target_y >=0 && target_y < renderer->viewport_height){
                char pixel_char = sprite->pixels[i * sprite->width + j];
                if(pixel_char != BLANK_CHARACTER){
                    int index = target_y * renderer->viewport_width + target_x;
                    renderer->buffer[index].Char.AsciiChar = pixel_char;
                }
            }
        }
    }
}

void renderer_present(Renderer *renderer){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {(SHORT)renderer->viewport_width, (SHORT)renderer->viewport_height};
    COORD bufferCoord = {0, 0};
    SMALL_RECT writeRegion = {0, 0, (SHORT)(renderer->viewport_width - 1), (SHORT)(renderer->viewport_height - 1)};
    WriteConsoleOutputA(hConsole, renderer->buffer, bufferSize, bufferCoord, &writeRegion);
}

void renderer_destroy(Renderer *renderer){
    if (renderer == NULL) return;
    free(renderer->buffer);
    free(renderer);
}