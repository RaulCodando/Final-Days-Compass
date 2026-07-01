#include "entity.h"
#include <stdlib.h>

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
    return entity;
}

void entity_init_collider(Entity* entity, float collider_width, float collider_height, float offset_x, float offset_y){
    if(!entity) return;
    
    entity->collider = collider_create(entity->x_pos + offset_x, entity->y_pos + offset_y, collider_width, collider_height);
    if(!entity->collider) return;

    entity->offset_x = offset_x;
    entity->offset_y = offset_y;
}

void entity_move_and_collide(Entity* entity, float vel_x, float vel_y, Map* map, SolidTileIDs* solid_tile_ids, Collider* colliders, int collider_count){
    if(!entity) return;

    if(!entity->collider){
        entity->x_pos += vel_x;
        entity->y_pos += vel_y;
        return;
    }

    if (!map || !solid_tile_ids || (collider_count > 0 && !colliders)) return;

    entity->collider->x = entity->x_pos + entity->offset_x;
    entity->collider->y = entity->y_pos + entity->offset_y;

    float vx = vel_x;
    float vy = vel_y;

    if(vx != 0.0f){
        float zero_y = 0.0f;
        float collider_x_start = entity->collider->x;
        resolve_map_collision(entity->collider, &vx, &zero_y, map, solid_tile_ids);
        if(collider_count > 0 && vx != 0.0f) {
            entity->collider->x = collider_x_start;
            resolve_custom_collision(entity->collider, &vx, &zero_y, colliders, collider_count);
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
    }

    entity->x_pos = entity->collider->x - entity->offset_x;
    entity->y_pos = entity->collider->y - entity->offset_y;
}

void entity_destroy(Entity *entity){
    if(!entity) return;
    game_object_destroy(&(entity->base));

    if(entity->collider){
        collider_destroy(entity->collider);
        entity->collider = NULL;
    }
    free(entity);
}