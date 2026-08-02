#include "player_behavior.h"
#include "../objects/entity.h"
#include "../core/game.h"
#include <math.h>

void player_update(Entity* self, Game* game){
    if(!self || !game) return;

    if (game->commands.move_left.active) self->vel_x = -4.0f * self->speed * game->delta_time;
    if (game->commands.move_right.active) self->vel_x = 4.0f * self->speed * game->delta_time;
    if (game->commands.move_up.active) self->vel_y = -4.0f * self->speed * game->delta_time;
    if (game->commands.move_down.active) self->vel_y = 4.0f * self->speed * game->delta_time;
    
    entity_move_and_collide(self, game->map, &game->solid_tile_ids, game->custom_colliders, game->entities);
}