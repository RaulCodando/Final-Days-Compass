#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

#include <stdbool.h>
#include <SDL3/SDL.h>

typedef struct Map Map;
typedef struct SolidTileIDs SolidTileIDs;
typedef struct Vector Vector;
typedef struct Collider Collider;
typedef struct SceneryElement SceneryElement;

bool init_world(SDL_Renderer *renderer, Map **map, SolidTileIDs *solid_tile_ids, const char *map_file, int tile_size, char *tile_ids, int tile_count, SDL_Color tile_color);
bool add_collider(Vector **colliders, float x, float y, float width, float height);
bool add_scenery_element(Vector **scenery_elements, SceneryElement *scenery_element);

#endif // WORLD_MANAGER_H