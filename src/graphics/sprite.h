#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>

typedef struct Sprite{
    SDL_Texture *texture;
    int height;
    int width;
} Sprite;

Sprite *sprite_create(SDL_Renderer *renderer, const char *path);
Sprite *sprite_create_blank(SDL_Renderer *renderer, int width, int height, SDL_Color color);
void sprite_destroy(Sprite *sprite);

#endif /* SPRITE_H */