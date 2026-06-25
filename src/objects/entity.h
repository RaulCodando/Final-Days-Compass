#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.h"

typedef struct Entity {
    GameObject base;
    
    int health;
    int standard_attack;
    float speed;
    float x_pos;
    float y_pos;
} Entity;

Entity *entity_create(ObjectIDs id, Sprite *sprite, int health, int standard_attack, float speed, float x_pos, float y_pos);
void entity_destroy(Entity *entity);

#endif //ENTITY_H