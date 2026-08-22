#include "dummy_entity.h"
#include "../core/game.h"
#include "../objects/entity.h"
#include "../asset_manager/asset_manager.h"
#include "../graphics/sprite.h"

static void test_entity_behavior_update(Entity *self, Game *game){
    if(!self || !game) return;

    self->vel_x = 4.0f * self->speed * game->delta_time;
    entity_move_and_collide(self, game->map, &game->solid_tile_ids, game->custom_colliders, game->entities);
}

bool test_entity_spawn(Game *game, float x, float y){
    if(!game) return false;

    Sprite *sprite = asset_manager_get(game->renderer->sdl_renderer, game->asset_manager, TEST_ENTITY, "tests/assets/test_entity_sprite.png", 12,32);
    if(!sprite) return false;

    Entity *test_entity = entity_create(TEST_ENTITY, sprite, NULL, 10.0f, x, y);
    if (!test_entity) return false;
    
    entity_init_collider(test_entity, 8.0f, 32.0f, 3.0f, 0.0f);
    test_entity->update_behavior = test_entity_behavior_update;

    return manage_entities_add(game, test_entity);
}