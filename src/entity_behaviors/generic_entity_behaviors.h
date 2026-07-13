#ifndef GENERIC_ENTITY_BEHAVIORS_H
#define GENERIC_ENTITY_BEHAVIORS_H

typedef struct Entity Entity;

void wrap_around_map(Entity* self, int map_width_px, int map_height_px);

#endif // GENERIC_ENTITY_BEHAVIORS_H