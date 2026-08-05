#include "player.h"
#include "../core/game.h"
#include "../objects/entity.h"
#include "../asset_manager/asset_manager.h"
#include "../graphics/sprite.h"
#include <math.h>

static void player_update(Entity* self, Game* game){
    if(!self || !game) return;

    if (game->commands.move_left.active) self->vel_x = -4.0f * self->speed * game->delta_time;
    if (game->commands.move_right.active) self->vel_x = 4.0f * self->speed * game->delta_time;
    if (game->commands.move_up.active) self->vel_y = -4.0f * self->speed * game->delta_time;
    if (game->commands.move_down.active) self->vel_y = 4.0f * self->speed * game->delta_time;
    
    entity_move_and_collide(self, game->map, &game->solid_tile_ids, game->custom_colliders, game->entities);
}

bool player_spawn(Game *game, float x, float y){
    if(!game) return false;

    Sprite *sprite = asset_manager_get(game->renderer->sdl_renderer, game->asset_manager, PLAYER, "assets/sprites/entity_sprites/player_sprite.png");
    if(!sprite) return false;

    Entity *player = entity_create(PLAYER, sprite, NULL, 10.0f, x, y);
    if (!player) return false;
    
    entity_init_collider(player, 10.0f, 2.0f, 1.0f, 30.0f);
    player->update_behavior = player_update;

    return manage_entities_add(game, player);
}