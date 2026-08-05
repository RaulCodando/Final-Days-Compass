#include "scenery_element.h"
#include <stdlib.h>

SceneryElement *scenery_element_create(ObjectIDs id, float x_pos, float y_pos, Sprite *sprite, float collider_offset_x, float collider_offset_y, float collider_width){
    SceneryElement *scenery_element = (SceneryElement*) malloc(sizeof(SceneryElement));
    if(!scenery_element) return NULL;
    scenery_element->base.id = id;
    scenery_element->x_pos = x_pos;
    scenery_element->y_pos = y_pos;
    scenery_element->base.sprite = sprite;
    scenery_element->collider_offset_x = collider_offset_x;
    scenery_element->collider_offset_y = collider_offset_y;
    scenery_element->collider_width = collider_width;
    return scenery_element;
}

float scenery_element_get_y_anchor(const SceneryElement *element) {
    if (!element) return 0.0f;
    if (element->base.sprite) return element->y_pos + element->base.sprite->height;
    return element->y_pos;
}

void scenery_element_destroy(SceneryElement *scenery_element){
    if(!scenery_element) return;
    free(scenery_element);
}