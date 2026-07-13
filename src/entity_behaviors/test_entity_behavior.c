#include "test_entity_behavior.h"
#include "../core/game.h"
#include "../objects/entity.h"

void test_entity_behavior_update(Entity *self, Game *game){
    if(!self || !game) return;

    self->vel_x = 2.0f * self->speed * game->delta_time;
    entity_move_and_collide(self, game->map, &game->solid_tile_ids, game->custom_colliders, game->entities);
}