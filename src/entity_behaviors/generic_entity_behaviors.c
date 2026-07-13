#include "generic_entity_behaviors.h"
#include "../objects/entity.h"

void wrap_around_map(Entity* self, int map_width_px, int map_height_px){
    if(!self) return;

    if(self->x_pos >= (float)map_width_px) self->x_pos = 0.0f - self->base.sprite->width;
    if(self->x_pos + self->base.sprite->width < 0) self->x_pos = (float)map_width_px - 1.0f;
    if(self->y_pos >= (float)map_height_px) self->y_pos = 0.0f - self->base.sprite->height;
    if(self->y_pos + self->base.sprite->height < 0) self->y_pos = (float)map_height_px - 1.0f;
}