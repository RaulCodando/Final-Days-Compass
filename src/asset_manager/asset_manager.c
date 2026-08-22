#include "asset_manager.h"
#include "../graphics/sprite.h"
#include <stdlib.h>

AssetManager* asset_manager_create(){
    AssetManager* asset_manager = (AssetManager*)malloc(sizeof(AssetManager));
    for (int i = 0; i < OBJECT_COUNT; i++) {
        asset_manager->objects_sprite_sheets[i] = NULL;
        asset_manager->object_sprites[i] = NULL;
    }
    return asset_manager;
}

void asset_manager_destroy(AssetManager* asset_manager) {
    if (asset_manager) {
        for (int i = 0; i < OBJECT_COUNT; i++) {
            if (asset_manager->object_sprites[i]) {
                sprite_destroy(asset_manager->object_sprites[i]);
            }
            if (asset_manager->objects_sprite_sheets[i]) {
                sprite_sheet_destroy(asset_manager->objects_sprite_sheets[i]);
            }
        }
        free(asset_manager);
    }
}

Sprite *asset_manager_get(SDL_Renderer *renderer, AssetManager *asset_manager, ObjectIDs id, const char *filepath, int frame_width, int frame_height){
    if(!asset_manager || id >= OBJECT_COUNT) return NULL;

    if (asset_manager->objects_sprite_sheets[id] == NULL) {
        asset_manager->objects_sprite_sheets[id] = sprite_sheet_create(renderer, filepath, frame_width, frame_height);
    }
    if (asset_manager->object_sprites[id] == NULL) {
        asset_manager->object_sprites[id] = sprite_create_from_sheet(asset_manager->objects_sprite_sheets[id], frame_width, frame_height);
    }
    return asset_manager->object_sprites[id];
}