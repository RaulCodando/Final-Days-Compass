#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>

// forward declaration
struct Sprite;

typedef struct Renderer {
    int viewport_width;
    int viewport_height;
    CHAR_INFO *buffer;
}Renderer;

Renderer *renderer_create(int width, int height);
void renderer_clear(Renderer *renderer);
void renderer_draw(Renderer *renderer, int x, int y, struct Sprite *sprite);
void renderer_present(Renderer *renderer);
void renderer_destroy(Renderer *renderer);

#endif //RENDERER_H