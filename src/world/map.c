#include "map.h"
#include <stdio.h>
#include <stdlib.h>

Map *map_create(int width, int height, int tile_size) {
    if (width <= 0 || height <= 0 || tile_size <= 0) return NULL;

    Map *map = malloc(sizeof(Map));
    if (!map) return NULL;
    
    map->width = width;
    map->height = height;
    map->tile_size = tile_size;

    map->tileset = tileset_create(tile_size, tile_size);
    if (!map->tileset) {
        free(map);
        return NULL;
    }

    map->tile_ids = (int*) malloc(width * height * sizeof(int));
    if (!map->tile_ids) {
        tileset_destroy(map->tileset);
        free(map);
        return NULL;
    }
    
    for(int i = 0; i < width * height; i++){
        map->tile_ids[i] = BLANK_TILE;
    }
    
    return map;
}

void map_destroy(Map *map) {
    if (!map) return;
    if (map->tile_ids) free(map->tile_ids);
    if (map->tileset) tileset_destroy(map->tileset);
    free(map);
}

void map_set_tile_id(Map *map, int x, int y, TileIDs id){
    if(!map || x < 0 || y < 0 || x >= map->width || y >= map->height) return;
    if(id < 0 || id >= TILE_COUNT) return;
    map->tile_ids[y * map->width + x] = id;
}

TileIDs map_get_tile_id(Map *map, int x, int y){
    if(!map || x < 0 || y < 0 || x >= map->width || y >= map->height) return BLANK_TILE;
    return (TileIDs) map->tile_ids[y * map->width + x];
}

Map *map_create_from_file(const char *filepath, int tile_size){
    FILE *file = fopen(filepath, "rb");
    if(!file) return NULL;

    char line[256];

    int width = 0;
    int height = 0;

    if(fgets(line, sizeof(line), file) != NULL){
        if(sscanf(line, "%d %d", &width, &height) != 2){
            fprintf(stderr, "Error: Invalid file format.\n");
            fclose(file);
            return NULL;
        }
    }

    if(width <=0 || height <=0){
        fprintf(stderr, "Error: Invalid dimensions.\n");
        fclose(file);
        return NULL;
    }

    Map *map = map_create(width, height, tile_size);
    if(!map) {
        fclose(file);
        return NULL;
    }

    for (int y = 0; y < height; y++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            fprintf(stderr, "Error: Unexpected end of file.\n");
            map_destroy(map);
            fclose(file);
            return NULL;
        }

        int real_length = 0;
        while(line[real_length] != '\0' && line[real_length] != '\n' && line[real_length] != '\r'){
            real_length++;
        }

        for (int x = 0; x < width; x++) {
            if(x < real_length){
                map_set_tile_id(map, x, y, (TileIDs) (line[x] - '0'));
            }
            else{
                map_set_tile_id(map, x, y, BLANK_TILE);
            }
        }
    }

    fclose(file);
    return map;
}