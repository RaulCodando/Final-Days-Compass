#include "collision.h"
#include "../objects/entity.h"
#include "../utils/vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Collider* collider_create(float x, float y, float width, float height) {
    Collider* collider = (Collider*)malloc(sizeof(Collider));
    if (collider == NULL) {
        perror("Failed to allocate memory for collider");
        return NULL;
    }
    collider->x = x;
    collider->y = y;
    collider->width = width;
    collider->height = height;
    return collider;
}

void solid_tile_ids_init(SolidTileIDs* solid_tile_ids, char* tile_ids, int tile_count) {
    solid_tile_ids->tile_count = tile_count;
    solid_tile_ids->solid_tile_ids = (char*)malloc(sizeof(char) * tile_count);
    if (solid_tile_ids->solid_tile_ids == NULL) {
        perror("Failed to allocate memory for solid tile ids");
        return;
    }
    for (int i = 0; i < tile_count; i++) {
        solid_tile_ids->solid_tile_ids[i] = tile_ids[i];
    }
}

bool is_collider_overlapping(Collider* collider_a, Collider* collider_b) {
    if (collider_a == NULL || collider_b == NULL) {
        return false; 
    }

    return (collider_a->x < collider_b->x + collider_b->width &&
            collider_a->x + collider_a->width > collider_b->x &&
            collider_a->y < collider_b->y + collider_b->height &&
            collider_a->y + collider_a->height > collider_b->y);
}

bool is_tile_solid(TileIDs id, SolidTileIDs* solid_tile_ids){
    if(!solid_tile_ids) return false;

    for(int i = 0; i < solid_tile_ids->tile_count; i++){
        if((char) id == solid_tile_ids->solid_tile_ids[i]){
            return true;
        }
    }
    return false;
}

void resolve_map_collision(Collider* collider, float* vel_x, float* vel_y, Map* map, SolidTileIDs* solid_tile_ids){
    if(!collider || !map || !solid_tile_ids || map->tile_size <= 0) return;

    if(*vel_x != 0.0f){
        collider->x += *vel_x;
        int start_x = (int) floor(collider->x / map->tile_size);
        int end_x   = (int) floor((collider->x + collider->width - 0.01f) / map->tile_size);
        int start_y = (int) floor(collider->y / map->tile_size);
        int end_y   = (int) floor((collider->y + collider->height - 0.01f) / map->tile_size);

        for(int y = start_y; y <= end_y; y++){
            for(int x = start_x; x <= end_x; x++){
                TileIDs current_tile_id = map_get_tile_id(map, x, y);
                if(is_tile_solid(current_tile_id, solid_tile_ids)){
                    if(*vel_x > 0.0f){
                        collider->x = x * map->tile_size - collider->width;
                    }
                    else if (*vel_x < 0.0f){
                        collider->x = x * map->tile_size + map->tile_size;
                    }
                    *vel_x = 0.0f;
                    break;
                }
            }
        }
    }

    if(*vel_y != 0.0f){
        collider->y += *vel_y;
        int start_x = (int) floor(collider->x / map->tile_size);
        int end_x   = (int) floor((collider->x + collider->width - 0.01f) / map->tile_size);
        int start_y = (int) floor(collider->y / map->tile_size);
        int end_y   = (int) floor((collider->y + collider->height - 0.01f) / map->tile_size);

        for(int y = start_y; y <= end_y; y++){
            for(int x = start_x; x <= end_x; x++){
                TileIDs current_tile_id = map_get_tile_id(map, x, y);
                if(is_tile_solid(current_tile_id, solid_tile_ids)){
                    if(*vel_y > 0.0f){
                        collider->y = y * map->tile_size - collider->height;
                    }
                    else if (*vel_y < 0.0f){
                        collider->y = y * map->tile_size + map->tile_size;
                    }
                    *vel_y = 0.0f;
                    break;
                }
            }
        }
    }
}

void resolve_custom_collision(Collider* target_collider, float* vel_x, float* vel_y, Vector* colliders){
    if(!target_collider || !colliders) return;

    if(*vel_x != 0.0f){
        target_collider->x += *vel_x;
        
        for(size_t i = 0; i < colliders->size; i++){
            Collider* current_collider = (Collider*)vector_get(colliders, i);
            if(current_collider == target_collider) continue;

            if(is_collider_overlapping(target_collider, current_collider)){
                if(*vel_x > 0.0f){
                    target_collider->x = current_collider->x - target_collider->width;
                }
                else if (*vel_x < 0.0f){
                    target_collider->x = current_collider->x + current_collider->width;
                }
                *vel_x = 0.0f;
                break;
            }
        }
    }

    if(*vel_y != 0.0f){
        target_collider->y += *vel_y;

        for(size_t i = 0; i < colliders->size; i++){
            Collider* current_collider = (Collider*)vector_get(colliders, i);
            if(current_collider == target_collider) continue;

            if(is_collider_overlapping(target_collider, current_collider)){
                if(*vel_y > 0.0f){
                    target_collider->y = current_collider->y - target_collider->height;
                }
                else if (*vel_y < 0.0f){
                    target_collider->y = current_collider->y + current_collider->height;
                }
                *vel_y = 0.0f;
                break;
            }
        }
    }
}

void resolve_entity_collision(Entity* target_entity, float* vel_x, float* vel_y, Vector* entities){
    if(!target_entity || !entities) return;

    Collider* target_collider = target_entity->collider;

    if(*vel_x != 0.0f){
        target_collider->x += *vel_x;
        
        for(size_t i = 0; i < entities->size; i++){
            Entity* current_entity = (Entity*)vector_get(entities, i);
            if(current_entity == target_entity || current_entity->collider == NULL) continue;

            if(is_collider_overlapping(target_collider, current_entity->collider)){
                if(*vel_x > 0.0f){
                    target_collider->x = current_entity->collider->x - target_collider->width;
                }
                else if (*vel_x < 0.0f){
                    target_collider->x = current_entity->collider->x + current_entity->collider->width;
                }
                *vel_x = 0.0f;
                break;
            }
        }
    }

    if(*vel_y != 0.0f){
        target_collider->y += *vel_y;

        for(size_t i = 0; i < entities->size; i++){
            Entity* current_entity = (Entity*)vector_get(entities, i);
            if(current_entity == target_entity || current_entity->collider == NULL) continue;

            if(is_collider_overlapping(target_collider, current_entity->collider)){
                if(*vel_y > 0.0f){
                    target_collider->y = current_entity->collider->y - target_collider->height;
                }
                else if (*vel_y < 0.0f){
                    target_collider->y = current_entity->collider->y + current_entity->collider->height;
                }
                *vel_y = 0.0f;
                break;
            }
        }
    }
}

void collider_destroy(Collider* collider){
    if(collider){
        free(collider);
    }
}

void solid_tile_ids_destroy(SolidTileIDs* solid_tile_ids){
    if(solid_tile_ids->solid_tile_ids){
        free(solid_tile_ids->solid_tile_ids);
        solid_tile_ids->solid_tile_ids = NULL;
    }
    solid_tile_ids->tile_count = 0;
}