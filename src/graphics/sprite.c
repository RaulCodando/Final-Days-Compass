#include "sprite.h"
#include <stdio.h>
#include <stdlib.h>
#include "../core/settings.h"
#include <SDL3_image/SDL_image.h>

SpriteSheet *sprite_sheet_create(SDL_Renderer *renderer, const char *path, int frame_width, int frame_height) {
    if (renderer == NULL || path == NULL) {
        fprintf(stderr, "Error: Invalid parameters passed to sprite_sheet_create.\n");
        return NULL;
    }

    SDL_Texture *texture = IMG_LoadTexture(renderer, path);
    if (texture == NULL) {
        fprintf(stderr, "Error: Could not load texture from %s: %s\n", path, SDL_GetError());
        return NULL;
    }

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    SpriteSheet *sprite_sheet = (SpriteSheet*) malloc(sizeof(SpriteSheet));
    if (sprite_sheet == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for SpriteSheet.\n");
        SDL_DestroyTexture(texture);
        return NULL;
    }

    float width = 0.0f;
    float height = 0.0f;
    SDL_GetTextureSize(texture, &width, &height);

    sprite_sheet->texture = texture;
    sprite_sheet->frame_width = frame_width;
    sprite_sheet->frame_height = frame_height;
    sprite_sheet->cols = (int)width / frame_width;
    sprite_sheet->rows = (int)height / frame_height;

    return sprite_sheet;
}

Sprite *sprite_create_from_sheet(SpriteSheet *spritesheet, int width, int height){
    if(!spritesheet || width <= 0 || height <= 0) return NULL;

    Sprite *sprite = (Sprite*) malloc(sizeof(Sprite));
    if (!sprite) return NULL;

    sprite->texture = spritesheet->texture;
    sprite->width = (float)width;
    sprite->height = (float)height;
    sprite->spritesheet = spritesheet;
    sprite->current_frame_index = 0;
    
    SDL_Rect frame = {
        0,
        0,
        width,
        height
    };

    sprite->frame = malloc(sizeof(SDL_Rect));
    if (!sprite->frame) {
        free(sprite);
        return NULL;
    }

    *(sprite->frame) = frame;

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
    sprite->spritesheet = NULL;
    sprite->current_frame_index = 0;

    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

    SDL_SetRenderTarget(renderer, sprite->texture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    return sprite;
}

void sprite_set_frame(Sprite *sprite, int frame_index) {
    if (!sprite || !sprite->spritesheet || !sprite->frame) return;

    int max_frames = sprite->spritesheet->cols * sprite->spritesheet->rows;
    if (frame_index < 0 || frame_index >= max_frames) {
        frame_index = 0;
    }

    sprite->current_frame_index = frame_index;

    int index_x = frame_index % sprite->spritesheet->cols;
    int index_y = frame_index / sprite->spritesheet->cols;

    sprite->frame->x = index_x * sprite->spritesheet->frame_width;
    sprite->frame->y = index_y * sprite->spritesheet->frame_height;
    sprite->frame->w = sprite->spritesheet->frame_width;
    sprite->frame->h = sprite->spritesheet->frame_height;
}

void sprite_destroy(Sprite *sprite) {
    if (!sprite) return;
    if (sprite->frame) free(sprite->frame);
    free(sprite);
}

void sprite_sheet_destroy(SpriteSheet *spritesheet) {
    if (spritesheet) {
        if (spritesheet->texture) {
            SDL_DestroyTexture(spritesheet->texture);
        }
        free(spritesheet);
    }
}