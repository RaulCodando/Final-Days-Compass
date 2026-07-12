#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.h"
#include "../physics/collision.h"
#include "../world/map.h"

typedef struct Entity {
    GameObject base;
    
    int health;
    int standard_attack;
    float speed;
    float vel_x;
    float vel_y;
    float x_pos;
    float y_pos;

    Collider* collider;
    float offset_x;
    float offset_y;
    float acc_x;
    float acc_y;
} Entity;

typedef struct Vector Vector;

Entity *entity_create(ObjectIDs id, Sprite *sprite, int health, int standard_attack, float speed, float x_pos, float y_pos);
void entity_init_collider(Entity* entity, float collider_width, float collider_height, float offset_x, float offset_y);
void entity_move_and_collide(Entity* entity, Map* map, SolidTileIDs* solid_tile_ids, Vector* colliders, Vector* entities);
void entity_destroy(Entity *entity);

#endif //ENTITY_H