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
    float x_pos;
    float y_pos;

    Collider* collider;
    float offset_x;
    float offset_y;
} Entity;

Entity *entity_create(ObjectIDs id, Sprite *sprite, int health, int standard_attack, float speed, float x_pos, float y_pos);
void entity_init_collider(Entity* entity, float collider_width, float collider_height, float offset_x, float offset_y);
void entity_move_and_collide(Entity* entity, float vel_x, float vel_y, Map* map, SolidTileIDs* solid_tile_ids, Collider* colliders, int collider_count);
void entity_destroy(Entity *entity);

#endif //ENTITY_H