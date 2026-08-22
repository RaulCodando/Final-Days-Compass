#include "renderer.h"
#include "sprite.h"
#include "../world/map.h"
#include "../core/settings.h"
#include "camera.h"
#include "../physics/collision.h"
#include "../ui/hud.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

Renderer *renderer_create(SDL_Window *window, int width, int height) {
    if (window == NULL) {
        fprintf(stderr, "Error: Invalid window provided to renderer_create.\n");
        return NULL;
    }

    Renderer *renderer = (Renderer*) malloc(sizeof(Renderer));
    if (renderer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Renderer struct.\n");
        return NULL;
    }

    renderer->viewport_width = width;
    renderer->viewport_height = height;

    renderer->sdl_renderer = SDL_CreateRenderer(window, NULL);

    if (renderer->sdl_renderer == NULL) {
        fprintf(stderr, "Error creating SDL_Renderer: %s\n", SDL_GetError());
        free(renderer);
        return NULL;
    }

    if (!TTF_Init()) {
        fprintf(stderr, "Error initializing TTF: %s\n", SDL_GetError());
    }

    renderer->font = TTF_OpenFont("assets/fonts/silkscreen/slkscr.ttf", 8);
    if (!renderer->font) {
        fprintf(stderr, "Warning: Could not load default font: %s\n", SDL_GetError());
    }

    SDL_Rect clip = {
        .x = 0,
        .y = 0,
        .w = (int)(renderer->viewport_width  * RENDER_SCALE),
        .h = (int)(renderer->viewport_height * RENDER_SCALE)
    };
    SDL_SetRenderClipRect(renderer->sdl_renderer, &clip);

    renderer_clear(renderer);
    return renderer;
}

RenderableObject *renderable_object_create(RenderableType type, void *object, float y_anchor){
    RenderableObject *renderable_object = (RenderableObject *) malloc(sizeof(RenderableObject));
    if(!renderable_object || !object) return NULL;

    renderable_object->type = type;
    renderable_object->object = object;
    renderable_object->y_anchor = y_anchor;
    return renderable_object;
}

void renderer_clear(Renderer *renderer) {
    if (renderer == NULL || renderer->sdl_renderer == NULL) return;

    SDL_SetRenderDrawColor(renderer->sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer->sdl_renderer);
}

void renderer_draw(Renderer *renderer, int x, int y, struct Sprite *sprite){
    if(!sprite || !renderer) return;

    SDL_FRect dst_rect = {
        .x = (float)x * RENDER_SCALE,
        .y = (float)y * RENDER_SCALE,
        .w = sprite->width * RENDER_SCALE,
        .h = sprite->height * RENDER_SCALE
    };

    SDL_RenderTexture(renderer->sdl_renderer, sprite->texture, NULL, &dst_rect);
}

void renderer_draw_tile(Renderer *renderer, int x, int y, enum TileIDs id, struct TileSet *tileset){
    if(!tileset || !renderer) return;

    Sprite *sprite = tileset_get_sprite(tileset, id);
    if (!sprite) return;
    renderer_draw(renderer, x, y, sprite);
}

void renderer_draw_map(Renderer *renderer, struct Camera *camera, struct Map *map, int layer){
    if(!map || !renderer || !camera) return;

    int start_j = (int)floorf((camera->x) / map->tile_size);
    int start_i = (int)floorf((camera->y) / map->tile_size);

    start_j = MAX(0, start_j);
    start_i = MAX(0, start_i);

    int tiles_in_viewport_x = (renderer->viewport_width + map->tile_size - 1) / map->tile_size;
    int tiles_in_viewport_y = (renderer->viewport_height + map->tile_size - 1) / map->tile_size;

    int end_j = start_j + tiles_in_viewport_x + 1;
    int end_i = start_i + tiles_in_viewport_y + 1;

    end_j = MIN(map->width, end_j);
    end_i = MIN(map->height, end_i);

    for(int i = start_i; i < end_i; i++){
        for(int j = start_j; j < end_j; j++){
            int target_x = (int) floorf((j * map->tile_size) - camera->x);
            int target_y = (int) floorf((i * map->tile_size) - camera->y);

            TileIDs current_tile = map_get_tile_id(map, j, i, layer);
            if(current_tile != BLANK_TILE) renderer_draw_tile(renderer, target_x, target_y, current_tile, map->tileset);
        }
    }
}

void renderer_present(Renderer *renderer){
    SDL_RenderPresent(renderer->sdl_renderer);
}

void renderer_draw_debug_collider(Renderer *renderer, struct Collider *collider, int collider_x, int collider_y) {
    if (!collider || !renderer) return;

    SDL_FRect rect = {
        .x = (float)collider_x * RENDER_SCALE,
        .y = (float)collider_y * RENDER_SCALE,
        .w = (float)collider->width * RENDER_SCALE,
        .h = (float)collider->height * RENDER_SCALE
    };

    SDL_SetRenderDrawColor(renderer->sdl_renderer, 255, 0, 0, 255);
    SDL_RenderRect(renderer->sdl_renderer, &rect);
}

void renderer_apply_dim(Renderer *renderer, float alpha) {
    if (!renderer) return;

    SDL_FRect rect = {
        .x = 0.0f * RENDER_SCALE,
        .y = 0.0f * RENDER_SCALE,
        .w = (float)renderer->viewport_width * RENDER_SCALE,
        .h = (float)renderer->viewport_height * RENDER_SCALE
    };

    SDL_SetRenderDrawBlendMode(renderer->sdl_renderer, SDL_BLENDMODE_BLEND);

    if (alpha < 0.0f) alpha = 0.0f;
    if (alpha > 1.0f) alpha = 1.0f;

    SDL_SetRenderDrawColor(renderer->sdl_renderer, 0, 0, 0, (Uint8)(alpha * 255.0f));
    SDL_RenderFillRect(renderer->sdl_renderer, &rect);
}

void renderer_draw_hud_element(Renderer *renderer, struct HudElement *element) {
    if (!renderer || !element) return;

    switch (element->type) {
        case HUD_CONTAINER: {
            HudContainerElement *container = element->data.container;
            if (!container) break;

            if (container->sprite) {
                Sprite *sprite = container->sprite;
                renderer_draw(renderer, element->x, element->y, sprite);
            }

            for (int i = 0; i < container->childCount; i++) {
                renderer_draw_hud_element(renderer, container->children[i]);
            }
            break;
        }

        case HUD_TEXT: {
            HudTextElement *text_elem = element->data.text;
            if (!text_elem || !text_elem->text || !renderer->font) break;

            SDL_Color color = {255, 255, 255, 255};
            SDL_Surface *surface = TTF_RenderText_Solid(renderer->font, text_elem->text, 0, color);
            if (!surface) break;

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer->sdl_renderer, surface);
            if (texture) {
                SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

                SDL_FRect dst_rect = {
                    .x = (float)element->x * RENDER_SCALE,
                    .y = (float)element->y * RENDER_SCALE,
                    .w = (float)surface->w * RENDER_SCALE,
                    .h = (float)surface->h * RENDER_SCALE
                };

                SDL_RenderTexture(renderer->sdl_renderer, texture, NULL, &dst_rect);
                SDL_DestroyTexture(texture);
            }

            SDL_DestroySurface(surface);
            break;
        }

        case HUD_ICON: {
            HudIconElement *icon = element->data.icon;
            if (!icon) break;

            Sprite *sprite = icon->sprite;
            if (sprite) {
                renderer_draw(renderer, element->x, element->y, sprite);
            }
            break;
        }
    }
}

void renderable_object_destroy(RenderableObject *renderable_object){
    if(!renderable_object) return;
    free(renderable_object);
}

void renderer_destroy(Renderer *renderer) {
    if (!renderer) return;
    if (renderer->font) TTF_CloseFont(renderer->font);
    if (renderer->sdl_renderer) SDL_DestroyRenderer(renderer->sdl_renderer);
    TTF_Quit();
    free(renderer);
}