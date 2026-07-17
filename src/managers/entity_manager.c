#include "entity_manager.h"
#include "../objects/entity.h"
#include "../graphics/sprite.h"
#include "../objects/asset_manager.h"
#include "../utils/vector.h"
#include "../core/game.h"
#include <stdio.h>
#include <stdlib.h>

bool init_entities(Vector **game_entities, AssetManager **asset_manager, ObjectIDs *object_ids, const char **sprite_paths, int sprite_count){
    if(sprite_count < 0 || (sprite_count == 0 && (object_ids != NULL || sprite_paths != NULL))) return false;

    *asset_manager = asset_manager_create();
    if(!*asset_manager) return false;

    *game_entities = vector_create();
    if(!*game_entities){
        asset_manager_destroy(*asset_manager);
        *asset_manager = NULL;
        return false;
    }

    if(sprite_count > 0 && object_ids != NULL && sprite_paths != NULL){
        for (int i = 0; i < sprite_count; i++) {
            if(sprite_paths[i] == NULL) {
                asset_manager_destroy(*asset_manager);
                vector_destroy(*game_entities, NULL);
                *asset_manager = NULL;
                *game_entities = NULL;
                return false;
            }

            Sprite *sprite = asset_manager_get(*asset_manager, object_ids[i], sprite_paths[i]);
            if(sprite == NULL){
                printf("Failed to load/get sprite path: %s\n", sprite_paths[i]);
                asset_manager_destroy(*asset_manager);
                vector_destroy(*game_entities, NULL);
                *asset_manager = NULL;
                *game_entities = NULL;
                return false;
            }
        }
    }

    return true;
}

bool add_entity(Vector **game_entities, AssetManager **asset_manager, int *game_entity_count, ObjectIDs id, int health, int standard_attack, float speed, float x_pos, float y_pos, const char *sprite_path){
    if(!game_entities || !(*game_entities) || !asset_manager || !(*asset_manager) || !game_entity_count || *game_entity_count < 0) return false;

    Sprite *sprite = asset_manager_get(*asset_manager, id, sprite_path);
    if(sprite == NULL) return false;

    Entity *entity = entity_create(id, sprite, health, standard_attack, speed, x_pos, y_pos);
    if(entity == NULL) return false;

    if(!vector_push(*game_entities, entity)){
        entity_destroy(entity);
        return false;
    }

    (*game_entity_count)++;

    return true;
}

bool add_entity_behavior(Vector **game_entities, ObjectIDs id, behavior_update behavior){
    if(!game_entities || !(*game_entities) || behavior == NULL) return false;

    bool added_behavior = false;
    
    for(size_t i = 0; i < (*game_entities)->size; i++){
        Entity *entity = (Entity *) vector_get(*game_entities, i);
        if(entity->base.id == id){
            entity->update_behavior = behavior;
            added_behavior = true;
        }
    }

    return added_behavior;
}

bool init_entity_collider(Vector **game_entities, ObjectIDs id, float collider_width, float collider_height, float offset_x, float offset_y){
    if(!game_entities || !(*game_entities)) return false;

    bool initialized_any = false;

    for(size_t i = 0; i < (*game_entities)->size; i++){
        Entity *entity = (Entity *) vector_get(*game_entities, i);
        if(entity->base.id == id){
            entity_init_collider(entity, collider_width, collider_height, offset_x, offset_y);
            initialized_any = true;
        }
    }

    return initialized_any;
}