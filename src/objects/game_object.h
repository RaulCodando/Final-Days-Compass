#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../graphics/sprite.h"

typedef enum ObjectIDs{
    PLAYER = 0,
    OBJECT_COUNT
} ObjectIDs;

typedef struct GameObject {
    ObjectIDs id;
    Sprite *sprite;
} GameObject;

void game_object_init(GameObject *game_object, ObjectIDs id, Sprite *sprite);
void game_object_destroy(GameObject *game_object);

#endif //GAME_OBJECT_H