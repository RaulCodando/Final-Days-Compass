#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "../objects/game_object.h"
#include <SDL3/SDL.h>

typedef struct AssetManager {
    SpriteSheet *objects_sprite_sheets[OBJECT_COUNT];
    Sprite *object_sprites[OBJECT_COUNT];
} AssetManager;

AssetManager* asset_manager_create();
void asset_manager_destroy(AssetManager* asset_manager);
Sprite* asset_manager_get(SDL_Renderer *renderer, AssetManager *asset_manager, ObjectIDs id, const char *filepath, int frame_width, int frame_height);

#endif //ASSET_MANAGER_H