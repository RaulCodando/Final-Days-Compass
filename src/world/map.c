#include "map.h"
#include <stdio.h>
#include <stdlib.h>

Map *map_create(SDL_Renderer *renderer, int width, int height, int layers, int tile_size, SDL_Color color) {
    if (width <= 0 || height <= 0 || tile_size <= 0 || layers <= 0) return NULL;

    Map *map = malloc(sizeof(Map));
    if (!map) return NULL;
    
    map->width = width;
    map->height = height;
    map->layers = layers;
    map->tile_size = tile_size;

    map->tileset = tileset_create(renderer, tile_size, tile_size, color);
    if (!map->tileset) {
        free(map);
        return NULL;
    }

    map->tile_ids = (int**) malloc(layers * sizeof(int*));
    if (!map->tile_ids) {
        tileset_destroy(map->tileset);
        free(map);
        return NULL;
    }

    for (int i = 0; i < layers; i++) {
        map->tile_ids[i] = (int*) malloc(width * height * sizeof(int));
        if (!map->tile_ids[i]) {
            for (int k = 0; k < i; k++) {
                free(map->tile_ids[k]);
            }
            free(map->tile_ids);
            tileset_destroy(map->tileset);
            free(map);
            return NULL;
        }
        for (int j = 0; j < width * height; j++) {
            map->tile_ids[i][j] = BLANK_TILE;
        }
    }
    
    return map;
}

void map_destroy(Map *map) {
    if (!map) return;
    
    if (map->tile_ids) {
        for (int i = 0; i < map->layers; i++) {
            if (map->tile_ids[i]) {
                free(map->tile_ids[i]);
            }
        }
        free(map->tile_ids);
    }
    
    if (map->tileset) tileset_destroy(map->tileset);
    free(map);
}

void map_set_tile_id(Map *map, int x, int y, int layer, TileIDs id) {
    if (!map || x < 0 || y < 0 || x >= map->width || y >= map->height) return;
    if (layer < 0 || layer >= map->layers) return;
    if (id < 0 || id >= TILE_COUNT) return;
    
    map->tile_ids[layer][y * map->width + x] = id;
}

TileIDs map_get_tile_id(Map *map, int x, int y, int layer) {
    if (!map || x < 0 || y < 0 || x >= map->width || y >= map->height) return BLANK_TILE;
    if (layer < 0 || layer >= map->layers) return BLANK_TILE;
    
    return (TileIDs) map->tile_ids[layer][y * map->width + x];
}

Map *map_create_from_file(SDL_Renderer *renderer, const char *filepath, int tile_size, SDL_Color color) {
    FILE *file = fopen(filepath, "r");
    if (!file) return NULL;

    char line[1024];

    int width = 0;
    int height = 0;
    int layers = 0;

    if (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%d %d %d", &width, &height, &layers) != 3) {
            fprintf(stderr, "Error: Invalid file format in header.\n");
            fclose(file);
            return NULL;
        }
    }

    if (width <= 0 || height <= 0 || layers <= 0) {
        fprintf(stderr, "Error: Invalid dimensions or layers.\n");
        fclose(file);
        return NULL;
    }

    Map *map = map_create(renderer, width, height, layers, tile_size, color);
    if (!map) {
        fclose(file);
        return NULL;
    }

    for (int l = 0; l < layers; l++) {
        for (int y = 0; y < height; y++) {
            if (fgets(line, sizeof(line), file) == NULL) {
                fprintf(stderr, "Error: Unexpected end of file at layer %d, line %d.\n", l, y + 1);
                map_destroy(map);
                fclose(file);
                return NULL;
            }

            if (line[0] == '\n' || line[0] == '\r') {
                y--;
                continue;
            }

            char *ptr = line;
            for (int x = 0; x < width; x++) {
                char *endptr;
                long tile_id = strtol(ptr, &endptr, 10);

                if (ptr == endptr) {
                    map_set_tile_id(map, x, y, l, BLANK_TILE);
                } else {
                    map_set_tile_id(map, x, y, l, (TileIDs)tile_id);
                    ptr = endptr;
                }
            }
        }
    }

    fclose(file);
    return map;
}