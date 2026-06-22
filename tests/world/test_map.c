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
} MapPixelBuffer;

MapPixelBuffer* create_map_pixel_buffer(Map *map){
    if (!map) return NULL;

    TileSet *tileset = tileset_create(8, 8);
    if (!tileset) return NULL;

    MapPixelBuffer *map_pixel_buffer = malloc(sizeof(MapPixelBuffer));
    if(!map_pixel_buffer) {
        tileset_destroy(tileset);
        return NULL;
    }

    map_pixel_buffer->height = map->height * map->tile_size;
    map_pixel_buffer->width = map->width * map->tile_size;
    map_pixel_buffer->pixels = malloc(map_pixel_buffer->height * map_pixel_buffer->width * sizeof(char));
    
    if(!map_pixel_buffer->pixels) {
        free(map_pixel_buffer);
        tileset_destroy(tileset);
        return NULL;
    }

    for(int i = 0; i < map->height; i++){
        for(int j = 0; j < map->width; j++){
            Sprite *current_tile = tileset_get_sprite(tileset, map_get_tile_id(map, j, i));
            
            for(int pi = 0; pi < map->tile_size; pi++){
                for(int pj = 0; pj < map->tile_size; pj++){
                    int target_y = (i * map->tile_size) + pi;
                    int target_x = (j * map->tile_size) + pj;
                    
                    if (current_tile && current_tile->pixels) {
                        int target_pixels = (pi * current_tile->width) + pj;
                        map_pixel_buffer->pixels[target_y * map_pixel_buffer->width + target_x] = current_tile->pixels[target_pixels];
                    } else {
                        map_pixel_buffer->pixels[target_y * map_pixel_buffer->width + target_x] = BLANK_CHARACTER;
                    }
                }
            }
        }
    }
    
    tileset_destroy(tileset);
    
    return map_pixel_buffer;
}

void print_map(Map *map){
    MapPixelBuffer *map_pixel_buffer = create_map_pixel_buffer(map);
    if(!map_pixel_buffer) return;

    for(int i = 0; i < map_pixel_buffer->height; i++){
        for(int j = 0; j < map_pixel_buffer->width; j++){
            printf("%c", map_pixel_buffer->pixels[i * map_pixel_buffer->width + j]);
        }
        printf("\n");
    }
    free(map_pixel_buffer->pixels);
    free(map_pixel_buffer);
}

void test_map_create(){
    Map *map = map_create(3, 3, 8);

    assert(map != NULL);
    assert(map->width == 3);
    assert(map->height == 3);
    assert(map->tile_size == 8);
    assert(map->tile_ids != NULL);

    print_map(map);
    printf("test_map_create passed successfully.\n");
    map_destroy(map);
}

void test_map_set_tile_id(){
    Map *map = map_create(3, 3, 8);
    
    map_set_tile_id(map, 0, 0, TEST_TILE01);
    assert(map->tile_ids[0] == TEST_TILE01);
    
    print_map(map);
    map_destroy(map);
    printf("test_map_set_tile_id passed successfully.\n");
}

void test_map_get_tile_id(){
    Map *map = map_create(3, 3, 8);
    
    map_set_tile_id(map, 1, 1, TEST_TILE01);
    
    assert(map_get_tile_id(map, 1, 1) == TEST_TILE01);
    assert(map_get_tile_id(map, -1, 0) == BLANK_TILE);
    assert(map_get_tile_id(map, 3, 1) == BLANK_TILE);
    assert(map_get_tile_id(map, 0, -1) == BLANK_TILE);
    assert(map_get_tile_id(map, 1, 3) == BLANK_TILE);

    map_destroy(map);
    printf("test_map_get_tile_id passed successfully.\n");
}

void test_map_create_from_file(){
    Map *map = map_create_from_file("tests/assets/test_tile_map01.txt", 8);
    assert(map != NULL);
    assert(map->width == 3);
    assert(map->height == 3);
    assert(map->tile_size == 8);
    assert(map->tile_ids != NULL);
    print_map(map);
    map_destroy(map);
    printf("test_map_create_from_file passed successfully.\n");
}

void test_map() {
    test_map_create();
    test_map_set_tile_id();
    test_map_get_tile_id();
    test_map_create_from_file();
    printf("All world map tests passed flawlessly!\n");
}