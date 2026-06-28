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
    entity->collider_width = 0;
    entity->collider_height = 0;
    entity->offset_x = 0;
    entity->offset_y = 0;
    return entity;
}

void entity_init_collider(Entity* entity, float collider_width, float collider_height, float offset_x, float offset_y){
    if(!entity) return;
    
    entity->collider = collider_create(entity->x_pos + offset_x, entity->y_pos + offset_y, collider_width, collider_height);
    if(!entity->collider) return;

    entity->collider_width = collider_width;
    entity->collider_height = collider_height;
    entity->offset_x = offset_x;
    entity->offset_y = offset_y;
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