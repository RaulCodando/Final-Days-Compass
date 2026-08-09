#include "scenery_element.h"
#include <stdlib.h>

SceneryElement *scenery_element_create(ObjectIDs id, float x_pos, float y_pos, Sprite *sprite){
    SceneryElement *scenery_element = (SceneryElement*) malloc(sizeof(SceneryElement));
    if(!scenery_element) return NULL;
    scenery_element->base.id = id;
    scenery_element->x_pos = x_pos;
    scenery_element->y_pos = y_pos;
    scenery_element->base.sprite = sprite;
    scenery_element_set_y_anchor(scenery_element);
    return scenery_element;
}

void scenery_element_set_y_anchor(SceneryElement *element){
    if(!element) return;
    if(element->base.sprite) element->y_anchor = element->y_pos + element->base.sprite->height;
    else element->y_anchor = element->y_pos;
}

void scenery_element_set_y_anchor_at_y_pos(SceneryElement *element, float y_pos){
    if(!element) return;
    element->y_anchor = y_pos;
}

void scenery_element_destroy(SceneryElement *scenery_element){
    if(!scenery_element) return;
    free(scenery_element);
}