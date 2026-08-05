#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.h"
#include "../physics/collision.h"
#include "../world/map.h"

typedef struct Game Game;

typedef void (*behavior_update)(Entity* self, Game *game_context);

typedef struct Entity {
    GameObject base;

    void *entity_data;
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

    behavior_update update_behavior;
} Entity;

typedef struct Vector Vector;

Entity *entity_create(ObjectIDs id, Sprite *sprite, void *entity_data, float speed, float x_pos, float y_pos);
void entity_init_collider(Entity* entity, float collider_width, float collider_height, float offset_x, float offset_y);
void entity_move_and_collide(Entity* entity, Map* map, SolidTileIDs* solid_tile_ids, Vector* colliders, Vector* entities);
void wrap_around_map(Entity* self, int map_width_px, int map_height_px);
float entity_get_y_anchor(Entity* entity);
void entity_destroy(Entity *entity);

#endif //ENTITY_H