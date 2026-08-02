#include "sprite.h"
#include <stdio.h>
#include <stdlib.h>
#include "../core/settings.h"
#include <SDL3_image/SDL_image.h>

Sprite *sprite_create(SDL_Renderer *renderer, const char *path) {
    if (renderer == NULL || path == NULL) {
        fprintf(stderr, "Error: Invalid parameters passed to sprite_create.\n");
        return NULL;
    }

    SDL_Texture *texture = IMG_LoadTexture(renderer, path);
    if (texture == NULL) {
        fprintf(stderr, "Error: Could not load texture from %s: %s\n", path, SDL_GetError());
        return NULL;
    }

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    Sprite *sprite = (Sprite*) malloc(sizeof(Sprite));
    if (sprite == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Sprite.\n");
        SDL_DestroyTexture(texture);
        return NULL;
    }

    float width = 0.0f;
    float height = 0.0f;
    SDL_GetTextureSize(texture, &width, &height);

    sprite->texture = texture;
    sprite->width = width;
    sprite->height = height;

    return sprite;
}

Sprite *sprite_create_blank(SDL_Renderer *renderer, int width, int height, SDL_Color color) {
    if (!renderer || width <= 0 || height <= 0) return NULL;

    Sprite *sprite = (Sprite*) malloc(sizeof(Sprite));
    if (!sprite) return NULL;

    sprite->texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_TARGET, 
        width, 
        height
    );

    if (!sprite->texture) {
        free(sprite);
        return NULL;
    }

    sprite->width = (float)width;
    sprite->height = (float)height;

    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

    SDL_SetRenderTarget(renderer, sprite->texture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    return sprite;
}

void sprite_destroy(Sprite *sprite) {
    if (sprite) {
        if (sprite->texture) {
            SDL_DestroyTexture(sprite->texture);
        }
        free(sprite);
    }
}