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
    return entity;
}

void entity_destroy(Entity *entity){
    if(!entity) return;
    game_object_destroy(&(entity->base));
    free(entity);
}