#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

#include <stdbool.h>

typedef struct Map Map;
typedef struct SolidTileIDs SolidTileIDs;
typedef struct Vector Vector;
typedef struct Collider Collider;

bool init_world(Map **map, SolidTileIDs *solid_tile_ids, const char *map_file, int tile_size, char *tile_ids, int tile_count);
bool init_colliders(Vector **colliders);
bool add_collider(Vector **colliders, float x, float y, float width, float height);

#endif // WORLD_MANAGER_H