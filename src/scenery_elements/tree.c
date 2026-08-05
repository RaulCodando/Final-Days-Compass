#include "tree.h"
#include "../core/game.h"
#include "../objects/scenery_element.h"
#include "../asset_manager/asset_manager.h"
#include "../managers/world_manager.h"
#include "../world/map.h"

bool build_tree(Game *game, float x, float y, float collider_offset_x, int collider_width){
    Sprite *sprite = asset_manager_get(game->renderer->sdl_renderer, game->asset_manager, TREE_LOG, "assets/sprites/scenery_element_sprites/TreeLogSprite.png");
    if(!sprite) return false;

    SceneryElement *scenery_element = scenery_element_create(TREE_LOG, x, y, sprite, collider_offset_x, sprite->height, collider_width);
    if(!scenery_element) return false;

    float collider_y = scenery_element_get_y_anchor(scenery_element) - 16;
    float collider_x = x + collider_offset_x;
    float width = (float) collider_width;
    float height = 16;

    manage_world_colliders_add(game, collider_x, collider_y, width, height);
    manage_world_scenery_elements_add(game, scenery_element);
    map_set_tile_id(game->map, (int) (x / 16), (int) (y / 16), 1, LEAVES_TILE);
    map_set_tile_id(game->map, (int) (x / 16) + 1, (int) (y / 16), 1, LEAVES_TILE);
    map_set_tile_id(game->map, (int) (x / 16) - 1, (int) (y / 16), 1, LEAVES_TILE);
    map_set_tile_id(game->map, (int) (x / 16), (int) (y / 16) - 1, 1, LEAVES_TILE);
    map_set_tile_id(game->map, (int) (x / 16) + 1, (int) (y / 16) - 1, 1, LEAVES_TILE);
    map_set_tile_id(game->map, (int) (x / 16) - 1, (int) (y / 16) - 1, 1, LEAVES_TILE);
    return true;
}