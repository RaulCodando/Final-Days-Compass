#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

#include <stdbool.h>

typedef struct Map Map;
typedef struct SolidTileIDs SolidTileIDs;

bool init_world(Map **map, SolidTileIDs *solid_tile_ids, const char *map_file, int tile_size, char *tile_ids, int tile_count);

#endif // WORLD_MANAGER_H