#include "test_map.h"
#include "../../src/world/map.h"
#include <assert.h>
#include "../../src/core/settings.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int height;
    int width;
    char *pixels;
} MapPixelsBuffer;

MapPixelsBuffer* create_map_pixels_buffer(Map *map){
    if (!map) return NULL;

    MapPixelsBuffer *map_pixels_buffer = malloc(sizeof(MapPixelsBuffer));
    if(!map_pixels_buffer) return NULL;

    map_pixels_buffer->height = map->height * map->tile_size;
    map_pixels_buffer->width = map->width * map->tile_size;
    map_pixels_buffer->pixels = malloc(map_pixels_buffer->height * map_pixels_buffer->width * sizeof(char));
    
    if(!map_pixels_buffer->pixels) {
        free(map_pixels_buffer);
        return NULL;
    }

    for(int i = 0; i < map->height; i++){
        for(int j = 0; j < map->width; j++){
            Sprite *current_tile = map_get_tile_sprite(map, j, i);
            
            for(int pi = 0; pi < map->tile_size; pi++){
                for(int pj = 0; pj < map->tile_size; pj++){
                    int target_y = (i * map->tile_size) + pi;
                    int target_x = (j * map->tile_size) + pj;
                    
                    int target_pixels = (pi * map->tile_size) + pj;
                    
                    if (current_tile && current_tile->pixels) {
                        map_pixels_buffer->pixels[target_y * map_pixels_buffer->width + target_x] = current_tile->pixels[target_pixels];
                    } else {
                        map_pixels_buffer->pixels[target_y * map_pixels_buffer->width + target_x] = BLANK_CHARACTER;
                    }
                }
            }
        }
    }
    
    return map_pixels_buffer;
}

void print_map(Map *map){
    MapPixelsBuffer *map_pixels_buffer = create_map_pixels_buffer(map);
    if(!map_pixels_buffer) return;

    for(int i = 0; i < map_pixels_buffer->height; i++){
        for(int j = 0; j < map_pixels_buffer->width; j++){
            printf("%c", map_pixels_buffer->pixels[i * map_pixels_buffer->width + j]);
        }
        printf("\n");
    }
    free(map_pixels_buffer->pixels);
    free(map_pixels_buffer);
}

void test_map_create(){
    Map *map = map_create(3, 3, 8);

    assert(map != NULL);
    assert(map->width == 3);
    assert(map->height == 3);
    assert(map->tile_size == 8);
    assert(map->tile_sprites != NULL);

    print_map(map);
    printf("test_map_create passed successfully.\n");
    map_destroy(map);
}

void test_map_set_tile_sprite(){
    Map *map = map_create(3, 3, 8);
    Sprite *tile_sprite = sprite_create("tests/assets/test_tile_sprite01.txt");
    assert(tile_sprite != NULL);
    
    map_set_tile_sprite(map, 0, 0, tile_sprite);
    assert(map->tile_sprites[0] == tile_sprite);
    
    print_map(map);
    
    map_destroy(map);
    sprite_destroy(tile_sprite); 
    
    printf("test_map_set_tile_sprite passed successfully.\n");
}

void test_map_get_tile_sprite(){
    Map *map = map_create(3, 3, 8);
    Sprite *tile_sprite = sprite_create("tests/assets/test_tile_sprite01.txt");
    assert(tile_sprite != NULL);
    
    map_set_tile_sprite(map, 1, 1, tile_sprite);
    
    assert(map_get_tile_sprite(map, 1, 1) == tile_sprite);
    assert(map_get_tile_sprite(map, -1, 0) == NULL);
    assert(map_get_tile_sprite(map, 3, 1) == NULL);
    assert(map_get_tile_sprite(map, 0, -1) == NULL);
    assert(map_get_tile_sprite(map, 1, 3) == NULL);

    map_destroy(map);
    sprite_destroy(tile_sprite);
    printf("test_map_get_tile_sprite passed successfully.\n");
}

void test_map() {
    test_map_create();
    test_map_set_tile_sprite();
    test_map_get_tile_sprite();
    printf("All world map tests passed flawlessly!\n");
}