#include "renderer.h"
#include "sprite.h"
#include "../world/map.h"
#include "../core/settings.h"
#include "camera.h"
#include "../physics/collision.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

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
    if(!sprite || !renderer) return;

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

void renderer_draw_tile(Renderer *renderer, int x, int y, enum TileIDs id, struct TileSet *tileset){
    if(!tileset || !renderer) return;

    Sprite *sprite = tileset_get_sprite(tileset, id);
    if (!sprite) return;
    renderer_draw(renderer, x, y, sprite);
}

void renderer_draw_map(Renderer *renderer, struct Camera *camera, struct Map *map){
    if(!map || !renderer || !camera) return;

    int start_j = (int)(camera->x) / map->tile_size;
    int start_i = (int)(camera->y) / map->tile_size;

    start_j = MAX(0, start_j);
    start_i = MAX(0, start_i);

    int tiles_in_viewport_x = (renderer->viewport_width + map->tile_size - 1) / map->tile_size;
    int tiles_in_viewport_y = (renderer->viewport_height + map->tile_size - 1) / map->tile_size;

    int end_j = start_j + tiles_in_viewport_x + 1;
    int end_i = start_i + tiles_in_viewport_y + 1;

    end_j = MIN(map->width, end_j);
    end_i = MIN(map->height, end_i);

    for(int i = start_i; i < end_i; i++){
        for(int j = start_j; j < end_j; j++){
            int target_x = (int) floorf((j * map->tile_size) - camera->x);
            int target_y = (int) floorf((i * map->tile_size) - camera->y);

            TileIDs current_tile = map_get_tile_id(map, j, i);
            renderer_draw_tile(renderer, target_x, target_y, current_tile, map->tileset);
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

void renderer_draw_debug_collider(Renderer *renderer, struct Collider *collider, int collider_x, int collider_y){
    if(!collider || !renderer) return;

    for(int i = 0; i < collider->height; i++){
        for(int j = 0; j < collider->width; j++){
            int target_x = collider_x + j;
            int target_y = collider_y + i;

            if(target_x >= 0 && target_x < renderer->viewport_width && target_y >=0 && target_y < renderer->viewport_height){
                int index = target_y * renderer->viewport_width + target_x;
                renderer->buffer[index].Char.AsciiChar = '?';
                renderer->buffer[index].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
            }
        }
    }
}

void renderer_destroy(Renderer *renderer){
    if (renderer == NULL) return;
    free(renderer->buffer);
    free(renderer);
}