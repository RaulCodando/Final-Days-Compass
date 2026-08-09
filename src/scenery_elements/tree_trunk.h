#ifndef TREE_TRUNK_H
#define TREE_TRUNK_H

#include <stdbool.h>
#include "../objects/scenery_element.h"

typedef struct Game Game;

bool build_tree_trunk(Game *game, float x, float y);

#endif // TREE_TRUNK_H