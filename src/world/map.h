#ifndef MAP_H
#define MAP_H

#include "../graphics/sprite.h"
#include "tiles.h"
#include <SDL3/SDL.h>

typedef struct Map {
    int width;
    int height;
    int tile_size;
    int *tile_ids;
    TileSet *tileset;
} Map;

Map *map_create(SDL_Renderer *renderer, int width, int height, int tile_size, SDL_Color color);
void map_destroy(Map *map);
void map_set_tile_id(Map *map, int x, int y, TileIDs id);
TileIDs map_get_tile_id(Map *map, int x, int y);
Map *map_create_from_file(SDL_Renderer *renderer, const char *filepath, int tile_size, SDL_Color color);

#endif /* MAP_H */