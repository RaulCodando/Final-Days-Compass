#ifndef SCENERY_ELEMENT_H
#define SCENERY_ELEMENT_H

#include "../graphics/sprite.h"
#include "../physics/collision.h"
#include "game_object.h"

typedef struct SceneryElement{
    GameObject base;

    float x_pos;
    float y_pos;
    float y_anchor;
} SceneryElement;

SceneryElement *scenery_element_create(ObjectIDs id, float x_pos, float y_pos, Sprite *sprite);
void scenery_element_set_y_anchor(SceneryElement *element);
void scenery_element_set_y_anchor_at_y_pos(SceneryElement *element, float y_pos);
void scenery_element_destroy(SceneryElement *scenery_element);

#endif // SCENERY_ELEMENT_H