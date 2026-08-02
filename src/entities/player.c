#include "player.h"
#include "../core/game.h"
#include "../objects/entity.h"
#include "../entity_behaviors/player_behavior.h"
#include "../objects/asset_manager.h"
#include "../graphics/sprite.h"

bool player_spawn(Game *game, float x, float y){
    if(!game) return false;

    Sprite *sprite = asset_manager_get(game->renderer->sdl_renderer, game->asset_manager, PLAYER, "tests/assets/test_player_sprite.png");
    if(!sprite) return false;

    Entity *player = entity_create(PLAYER, sprite, NULL, 10.0f, x, y);
    if (!player) return false;
    
    entity_init_collider(player, 6.0f, 32.0f, 3.0f, 0.0f);
    player->update_behavior = player_update;

    return manage_entities_add(game, player);
}