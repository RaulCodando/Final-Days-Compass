#include "entity.h"
#include "../utils/vector.h"
#include <stdlib.h>
#include <math.h>

Entity* entity_create(ObjectIDs id, Sprite *sprite, int health, int standard_attack, float speed, float x_pos, float y_pos){
    Entity *entity = (Entity *) malloc(sizeof(Entity));
    if(!entity) return NULL;
    game_object_init(&(entity->base), id, sprite);
    entity->health = health;
    entity->standard_attack = standard_attack;
    entity->speed = speed;
    entity->x_pos = x_pos;
    entity->y_pos = y_pos;
    entity->collider = NULL;
    entity->offset_x = 0.0f;
    entity->offset_y = 0.0f;
    entity->acc_x = 0.0f;
    entity->acc_y = 0.0f;
    entity->vel_x = 0.0f;
    entity->vel_y = 0.0f;
    return entity;
}

void entity_init_collider(Entity* entity, float collider_width, float collider_height, float offset_x, float offset_y){
    if(!entity) return;
    
    entity->collider = collider_create(entity->x_pos + offset_x, entity->y_pos + offset_y, collider_width, collider_height);
    if(!entity->collider) return;

    entity->offset_x = offset_x;
    entity->offset_y = offset_y;
}

void entity_move_and_collide(Entity* entity, Map* map, SolidTileIDs* solid_tile_ids, Collider* colliders, int collider_count, Vector* entities){
    if(!entity) return;

    if(!entity->collider){
        entity->x_pos += entity->vel_x;
        entity->y_pos += entity->vel_y;
        return;
    }

    if (!map || !solid_tile_ids || (collider_count > 0 && !colliders)) return;

    entity->collider->x = entity->x_pos + entity->offset_x;
    entity->collider->y = entity->y_pos + entity->offset_y;

    if ((entity->vel_x > 0.0f && entity->acc_x < 0.0f) || (entity->vel_x < 0.0f && entity->acc_x > 0.0f)) entity->acc_x = 0.0f;
    if ((entity->vel_y > 0.0f && entity->acc_y < 0.0f) || (entity->vel_y < 0.0f && entity->acc_y > 0.0f)) entity->acc_y = 0.0f;

    entity->acc_x += entity->vel_x;
    entity->acc_y += entity->vel_y;

    float move_x = truncf(entity->acc_x);
    float move_y = truncf(entity->acc_y);

    entity->acc_x -= move_x;
    entity->acc_y -= move_y;

    if (move_x == 0.0f && move_y == 0.0f) return;

    float vx = move_x;
    float vy = move_y;

    if(vx != 0.0f){
        float zero_y = 0.0f;
        float collider_x_start = entity->collider->x;
        resolve_map_collision(entity->collider, &vx, &zero_y, map, solid_tile_ids);
        if(collider_count > 0 && vx != 0.0f) {
            entity->collider->x = collider_x_start;
            resolve_custom_collision(entity->collider, &vx, &zero_y, colliders, collider_count);
        }
        if(entities && entities->size > 0 && vx != 0.0f) {
            entity->collider->x = collider_x_start;
            resolve_entity_collision(entity, &vx, &zero_y, entities);
        }
    }

    if(vy != 0.0f){
        float zero_x = 0.0f; 
        float collider_y_start = entity->collider->y;
        resolve_map_collision(entity->collider, &zero_x, &vy, map, solid_tile_ids);
        if(collider_count > 0 && vy != 0.0f) {
            entity->collider->y = collider_y_start; 
            resolve_custom_collision(entity->collider, &zero_x, &vy, colliders, collider_count);
        }
        if(entities && entities->size > 0 && vy != 0.0f) {
            entity->collider->y = collider_y_start; 
            resolve_entity_collision(entity, &zero_x, &vy, entities);
        }
    }

    entity->x_pos = entity->collider->x - entity->offset_x;
    entity->y_pos = entity->collider->y - entity->offset_y;
}

void entity_destroy(Entity *entity){
    if(!entity) return;

    if(entity->collider){
        collider_destroy(entity->collider);
        entity->collider = NULL;
    }
    free(entity);
}