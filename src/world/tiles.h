#ifndef TILES_H
#define TILES_H

#include <stdbool.h>
#include <SDL3/SDL.h>
#include "../core/id.h"
#include "../graphics/sprite.h"

typedef struct Tile {
    ID id;
    int frame_index;
    bool is_solid;  
} Tile;

typedef struct TileSet {
    SpriteSheet *spritesheet; 
    Sprite *render_sprite;    
} TileSet;

TileSet *tileset_create(SpriteSheet *sheet);
void tileset_destroy(TileSet *tileset);
void tileset_render_tile(SDL_Renderer *renderer, TileSet *tileset, Tile *tile, int screen_x, int screen_y);

#endif // TILES_H