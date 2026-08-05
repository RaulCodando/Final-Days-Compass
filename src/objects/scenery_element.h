#ifndef SCENERY_ELEMENT_H
#define SCENERY_ELEMENT_H

#include "../graphics/sprite.h"
#include "../physics/collision.h"
#include "game_object.h"

typedef struct SceneryElement{
    GameObject base;

    float x_pos;
    float y_pos;
    float collider_offset_x;
    float collider_offset_y;
    float collider_width;
} SceneryElement;

SceneryElement *scenery_element_create(ObjectIDs id, float x_pos, float y_pos, Sprite *sprite, float collider_offset_x, float collider_offset_y, float collider_width);
float scenery_element_get_y_anchor(const SceneryElement *element);
void scenery_element_destroy(SceneryElement *scenery_element);

#endif // SCENERY_ELEMENT_H