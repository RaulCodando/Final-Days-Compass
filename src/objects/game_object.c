#include "game_object.h"

void game_object_init(GameObject *game_object, ObjectIDs id, Sprite *sprite){
    if(!game_object || id >= OBJECT_COUNT || !sprite) return;
    game_object->id = id;
    game_object->sprite = sprite;
}