#ifndef SPRITE_H
#define SPRITE_H

typedef struct Sprite{
    int height;
    int width;
    char *pixels;
} Sprite;

Sprite *sprite_create(char *path);
Sprite *sprite_create_blank(int width, int height);
void sprite_destroy(Sprite *sprite);

#endif /* SPRITE_H */