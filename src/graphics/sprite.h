#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>

typedef struct SpriteSheet{
    SDL_Texture *texture;
    int frame_width;
    int frame_height;
    int cols;
    int rows;
} SpriteSheet;

typedef struct Sprite{
    SpriteSheet *spritesheet;
    SDL_Rect *frame;
    int current_frame_index;
    int width;
    int height;
} Sprite;

SpriteSheet *sprite_sheet_create(SDL_Renderer *renderer, const char *path, int frame_width, int frame_height);
Sprite *sprite_create_from_sheet(SpriteSheet *spritesheet, int width, int height);
Sprite *sprite_create_blank(SDL_Renderer *renderer, int width, int height, SDL_Color color);
void sprite_set_frame(Sprite *sprite, int frame_index);
void sprite_destroy(Sprite *sprite);
void sprite_sheet_destroy(SpriteSheet *spritesheet);

#endif /* SPRITE_H */