#include "tiles.h"
#include <stdlib.h>

TileSet *tileset_create(SDL_Renderer *renderer,int width, int height, SDL_Color color){
    TileSet *tileset = (TileSet*) malloc(sizeof(TileSet));
    if(!tileset) return NULL;

    for(int i = 0; i < TILE_COUNT; i++) {
        tileset->sprites[i] = NULL;
    }

    tileset->sprites[0] = sprite_create_blank(renderer, width, height, color);
    tileset->sprites[1] = sprite_create(renderer, "assets/sprites/tile_sprites/GrassTile.png");
    tileset->sprites[2] = sprite_create(renderer, "assets/sprites/tile_sprites/WaterTile.png");

    for(int i = 0; i < TILE_COUNT; i++) {
        if(!tileset->sprites[i]){
            tileset_destroy(tileset);
            return NULL;
        }
    }

    return tileset;
}

void tileset_destroy(TileSet *tileset){
    if(!tileset) return;
    for(int i = 0; i < TILE_COUNT; i++){
        sprite_destroy(tileset->sprites[i]);
    }
    free(tileset);
}

Sprite *tileset_get_sprite(TileSet *tileset, TileIDs ID){
    if(!tileset || ID < 0 || ID >= TILE_COUNT) return NULL;
    return tileset->sprites[ID];
}