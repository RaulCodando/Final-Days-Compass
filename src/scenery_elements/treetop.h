#ifndef TREETOP_H
#define TREETOP_H

#include <stdbool.h>
#include "../objects/scenery_element.h"

typedef struct Game Game;

SceneryElement *build_treetop(Game *game, float x, float y);

#endif // TREETOP_H