#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

struct Sprite;
struct Map;
enum TileIDs;
struct TileSet;
struct Camera;
struct Collider;
struct HudElement;

typedef struct Renderer {
    SDL_Renderer *sdl_renderer;
    int viewport_width;
    int viewport_height;
    TTF_Font *font;
}Renderer;

Renderer *renderer_create(SDL_Window *window, int width, int height);
void renderer_clear(Renderer *renderer);
void renderer_draw(Renderer *renderer, int x, int y, struct Sprite *sprite);
void renderer_draw_tile(Renderer *renderer, int x, int y, enum TileIDs id, struct TileSet *tileset);
void renderer_draw_map(Renderer *renderer, struct Camera *camera, struct Map *map);
void renderer_present(Renderer *renderer);
void renderer_draw_debug_collider(Renderer *renderer, struct Collider *collider, int collider_x, int collider_y);
void renderer_apply_dim(Renderer *renderer, float alpha);
void renderer_draw_hud_element(Renderer *renderer, struct HudElement *element);
void renderer_destroy(Renderer *renderer);

#endif //RENDERER_H