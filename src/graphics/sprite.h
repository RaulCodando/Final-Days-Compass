#ifndef SPRITE_H
#define SPRITE_H

typedef struct {
    int height;
    int width;
    char *pixels;
} Sprite;

Sprite *sprite_create(char *path);
void sprite_destroy(Sprite *sprite);

#endif /* SPRITE_H */