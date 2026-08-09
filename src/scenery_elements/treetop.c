#include "treetop.h"
#include "../core/game.h"
#include "../objects/scenery_element.h"
#include "../asset_manager/asset_manager.h"
#include "../managers/world_manager.h"

SceneryElement *build_treetop(Game *game, float x, float y){
    Sprite *sprite = asset_manager_get(game->renderer->sdl_renderer, game->asset_manager, TREE_TOP, "assets/sprites/scenery_element_sprites/TreeTopSprite.png");
    if(!sprite) return NULL;

    SceneryElement *scenery_element = scenery_element_create(TREE_TOP, x, y, sprite);
    if(!scenery_element) return NULL;

    manage_world_scenery_elements_add(game, scenery_element);
    return scenery_element;
}