#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include "../objects/scenery_element.h"

typedef struct Game Game;

bool build_tree(Game *game, float x, float y, float collider_offset_x, int collider_width);

#endif // TREE_H