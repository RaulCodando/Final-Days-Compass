#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.h"
#include "../physics/collision.h"

typedef struct Entity {
    GameObject base;
    
    int health;
    int standard_attack;
    float speed;
    float x_pos;
    float y_pos;

    Collider* collider;
    float collider_width;
    float collider_height;
    float offset_x;
    float offset_y;
} Entity;

Entity *entity_create(ObjectIDs id, Sprite *sprite, int health, int standard_attack, float speed, float x_pos, float y_pos);
void entity_init_collider(Entity* entity, float collider_width, float collider_height, float offset_x, float offset_y);
void entity_destroy(Entity *entity);

#endif //ENTITY_H