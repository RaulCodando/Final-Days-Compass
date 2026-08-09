#include "tree.h"
#include "tree_trunk.h"
#include "treetop.h"
#include "../objects/scenery_element.h"
#include "../core/game.h"

bool build_tree(Game *game, float x, float y){
    if(!build_tree_trunk(game, x, y)) return false;

    SceneryElement *treetop = build_treetop(game, x - 48, y - 32);
    if(!treetop) return false;

    scenery_element_set_y_anchor_at_y_pos(treetop, y + 81);
    return true;
}