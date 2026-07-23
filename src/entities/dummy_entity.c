#include "dummy_entity.h"
#include "../core/game.h"
#include "../objects/entity.h"
#include "../entity_behaviors/test_entity_behavior.h"
#include "../objects/asset_manager.h"
#include "../graphics/sprite.h"

bool test_entity_spawn(Game *game, float x, float y){
    if(!game) return false;

    Sprite *sprite = asset_manager_get(game->asset_manager, TEST_ENTITY, "tests/assets/test_entity_sprite.txt");
    if(!sprite) return false;

    Entity *test_entity = entity_create(TEST_ENTITY, sprite, NULL, 10.0f, x, y);
    if (!test_entity) return false;
    
    entity_init_collider(test_entity, 4.0f, 8.0f, 2.0f, 0.0f);
    test_entity->update_behavior = test_entity_behavior_update;

    return manage_entities_add(game, test_entity);
}