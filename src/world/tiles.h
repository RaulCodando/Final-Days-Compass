#ifndef TILES_H
#define TILES_H

#include "../graphics/sprite.h"
#include <SDL3/SDL.h>

typedef struct Renderer Renderer;

typedef enum TileIDs{
    BLANK_TILE,
    GRASS_TILE,
    WATER_TILE,
    TILE_COUNT
} TileIDs;

typedef struct TileSet{
    Sprite *sprites[TILE_COUNT];
} TileSet;

TileSet *tileset_create(SDL_Renderer *renderer, int width, int height, SDL_Color color);
void tileset_destroy(TileSet *tileset);
Sprite *tileset_get_sprite(TileSet *tileset, TileIDs ID);

#endif // TILES_H