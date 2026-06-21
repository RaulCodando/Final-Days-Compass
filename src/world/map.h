#ifndef MAP_H
#define MAP_H

#include "../graphics/sprite.h"

typedef struct Map {
    int width;
    int height;
    int tile_size;
    Sprite **tile_sprites;
} Map;

Map *map_create(int width, int height, int tile_size);
void map_destroy(Map *map);
void map_set_tile_sprite(Map *map, int x, int y, Sprite *tile_sprite);
Sprite* map_get_tile_sprite(Map *map, int x, int y);

#endif /* MAP_H */