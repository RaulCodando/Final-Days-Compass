#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "game_object.h"
#include <SDL3/SDL.h>

typedef struct AssetManager {
    Sprite *object_sprites[OBJECT_COUNT];
} AssetManager;

AssetManager* asset_manager_create();
void asset_manager_destroy(AssetManager* asset_manager);
Sprite* asset_manager_get(SDL_Renderer *renderer, AssetManager* asset_manager, ObjectIDs id, const char *filepath);

#endif //ASSET_MANAGER_H