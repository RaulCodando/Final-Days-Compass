#include "tree_trunk.h"
#include "../core/game.h"
#include "../objects/scenery_element.h"
#include "../asset_manager/asset_manager.h"
#include "../managers/world_manager.h"

bool build_tree_trunk(Game *game, float x, float y){
    Sprite *sprite = asset_manager_get(game->renderer->sdl_renderer, game->asset_manager, TREE_LOG, "assets/sprites/scenery_element_sprites/TreeLogSprite.png");
    if(!sprite) return false;

    SceneryElement *scenery_element = scenery_element_create(TREE_LOG, x, y, sprite);
    if(!scenery_element) return false;

    float collider_y = scenery_element->y_anchor - 16;
    float collider_x = x;
    float width = 16.0f;
    float height = 16.0f;

    manage_world_colliders_add(game, collider_x, collider_y, width, height);
    manage_world_scenery_elements_add(game, scenery_element);
    return true;
}