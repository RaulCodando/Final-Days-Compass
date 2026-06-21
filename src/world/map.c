#include "map.h"
#include <stdlib.h>

Map *map_create(int width, int height, int tile_size) {
    Map *map = malloc(sizeof(Map));
    if (!map) return NULL;
    
    map->width = width;
    map->height = height;
    map->tile_size = tile_size;
    
    map->tile_sprites = (Sprite**) malloc(width * height * sizeof(Sprite*));
    if (!map->tile_sprites) {
        free(map);
        return NULL;
    }

    Sprite *blank_sprite = sprite_create_blank(tile_size, tile_size);
    if(!blank_sprite) {
        free(map->tile_sprites);
        free(map);
        return NULL;
    }
    
    for(int i = 0; i < width * height; i++){
        map->tile_sprites[i] = blank_sprite;
    }
    
    return map;
}

void map_destroy(Map *map){
    if(!map) return;
    
    if (map->tile_sprites && map->width * map->height > 0) {
        Sprite *blank_sprite = map->tile_sprites[0];
        if (blank_sprite) {
            sprite_destroy(blank_sprite);
        }
    }

    free(map->tile_sprites);
    free(map);
}

void map_set_tile_sprite(Map *map, int x, int y, Sprite *tile_sprite){
    if(!map || x < 0 || y < 0 || x >= map->width || y >= map->height) return;
    if(!tile_sprite || tile_sprite->width != map->tile_size || tile_sprite->height != map->tile_size) return;
    map->tile_sprites[y * map->width + x] = tile_sprite;
}

Sprite* map_get_tile_sprite(Map *map, int x, int y){
    if(!map || x < 0 || y < 0 || x >= map->width || y >= map->height) return NULL;
    return map->tile_sprites[y * map->width + x];
}