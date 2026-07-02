#ifndef COLLISION_H
#define COLLISION_H

#include "../world/tiles.h"
#include "../world/map.h"
#include <stdbool.h>

typedef struct {
    int tile_count;
    char* solid_tile_ids;
} SolidTileIDs;

typedef struct Collider {
    float x;
    float y;
    float width;
    float height;
} Collider;

Collider* collider_create(float x, float y, float width, float height);
void solid_tile_ids_init(SolidTileIDs* solid_tile_ids, char* tile_ids, int tile_count);
bool is_collider_overlapping(Collider* collider_a, Collider* collider_b);
bool is_tile_solid(TileIDs id, SolidTileIDs* solid_tile_ids);
void resolve_map_collision(Collider* collider, float* vel_x, float* vel_y, Map* map, SolidTileIDs* solid_tile_ids);
void resolve_custom_collision(Collider* target_collider, float* vel_x, float* vel_y, Collider* colliders, int collider_count);
void collider_destroy(Collider* collider);
void solid_tile_ids_destroy(SolidTileIDs* solid_tile_ids);

#endif // COLLISION_H