#ifndef TILES_H
#define TILES_H

#include "../graphics/sprite.h"

typedef enum TileIDs{
    BLANK_TILE,
    TEST_TILE01,
    TEST_TILE02,
    TEST_TILE03,
    TILE_COUNT
} TileIDs;

typedef struct TileSet{
    Sprite *sprites[TILE_COUNT];
} TileSet;

TileSet *tileset_create(int width, int height);
void tileset_destroy(TileSet *tileset);
Sprite *tileset_get_sprite(TileSet *tileset, TileIDs ID);

#endif // TILES_H