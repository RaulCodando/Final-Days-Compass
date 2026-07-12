#include "world_manager.h"
#include "../world/map.h"
#include "../physics/collision.h"
#include "../utils/vector.h"
#include <stdio.h>
#include <stdlib.h>

bool init_world(Map **map, SolidTileIDs *solid_tile_ids, const char *map_file, int tile_size, char *tile_ids, int tile_count){
    if (!map || !solid_tile_ids || !map_file || tile_size <= 0) return false;
    
    solid_tile_ids_init(solid_tile_ids, tile_ids, tile_count);

    *map = map_create_from_file(map_file, tile_size);
    if(*map == NULL){
        solid_tile_ids_destroy(solid_tile_ids);
        return false;
    }

    return true;
}

bool init_colliders(Vector **colliders){
    if (!colliders) return false;
    *colliders = vector_create();
    if(!*colliders) return false;
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