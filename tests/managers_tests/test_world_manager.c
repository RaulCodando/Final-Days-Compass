#include "test_world_manager.h"
#include "../../src/managers/world_manager.h"
#include "../../src/world/map.h"
#include "../../src/physics/collision.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_init_world(void){
    Map *map = NULL;
    SolidTileIDs solid_tile_ids; 
    
    const char *map_file = "tests/assets/test_tile_map03.txt";
    int tile_size = 8;
    char *tile_ids = "1";
    int tile_count = 1;

    bool result = init_world(&map, &solid_tile_ids, map_file, tile_size, tile_ids, tile_count);

    assert(result == true);
    assert(map != NULL);
    assert(solid_tile_ids.tile_count == tile_count);
    assert(map->tile_size == tile_size);

    solid_tile_ids_destroy(&solid_tile_ids);
    map_destroy(map);

    printf("test_init_world passed\n");
}