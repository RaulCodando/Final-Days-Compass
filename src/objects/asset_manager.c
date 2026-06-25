#include "asset_manager.h"
#include <stdlib.h>

AssetManager* asset_manager_create(){
    AssetManager* asset_manager = (AssetManager*)malloc(sizeof(AssetManager));
    for (int i = 0; i < OBJECT_COUNT; i++) {
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
        }
        free(asset_manager);
    }
}

Sprite *asset_manager_get(AssetManager *asset_manager, ObjectIDs id, const char *filepath){
    if(!asset_manager || id >= OBJECT_COUNT) return NULL;

    if (asset_manager->object_sprites[id] == NULL) {
        asset_manager->object_sprites[id] = sprite_create(filepath);
    }
    return asset_manager->object_sprites[id];
}