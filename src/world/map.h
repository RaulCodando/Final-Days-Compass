#ifndef MAP_H
#define MAP_H

#include "../graphics/sprite.h"
#include "tiles.h"

typedef struct Map {
    int width;
    int height;
    int tile_size;
    int *tile_ids;
} Map;

Map *map_create(int width, int height, int tile_size);
void map_destroy(Map *map);
void map_set_tile_id(Map *map, int x, int y, TileIDs id);
TileIDs map_get_tile_id(Map *map, int x, int y);
Map *map_create_from_file(const char *filepath, int tile_size);

#endif /* MAP_H */