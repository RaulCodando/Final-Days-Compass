#include "world_manager.h"
#include "../world/map.h"
#include "../physics/collision.h"
#include "../utils/vector.h"
#include "../objects/scenery_element.h"
#include <stdio.h>
#include <stdlib.h>

bool init_world(SDL_Renderer *renderer, Map **map, SolidTileIDs *solid_tile_ids, const char *map_file, int tile_size, char *tile_ids, int tile_count, SDL_Color tile_color){
    if (!map || !solid_tile_ids || !map_file || tile_size <= 0) return false;
    
    solid_tile_ids_init(solid_tile_ids, tile_ids, tile_count);

    *map = map_create_from_file(renderer, map_file, tile_size, tile_color);
    if(*map == NULL){
        solid_tile_ids_destroy(solid_tile_ids);
        return false;
    }

    return true;
}

bool add_collider(Vector **colliders, float x, float y, float width, float height){
    if(!colliders || !(*colliders)) return false;
    Collider *collider = collider_create(x, y, width, height);
    if(collider == NULL) return false;
    if(!vector_push(*colliders, collider)){
        collider_destroy(collider);
        return false;
    }
    return true;
}

bool add_scenery_element(Vector **scenery_elements, SceneryElement *scenery_element){
    if(!scenery_elements || !(*scenery_elements) || !scenery_element) return false;
    
    if(!vector_push(*scenery_elements, scenery_element)){
        scenery_element_destroy(scenery_element);
        return false;
    }
    
    return true;
}