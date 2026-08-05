#ifndef GAME_H
#define GAME_H

#include "../graphics/renderer.h"
#include "../graphics/camera.h"
#include "../input/commands.h"
#include "../asset_manager/asset_manager.h"
#include "../input/keyboard.h"
#include "../objects/entity.h"
#include "../objects/scenery_element.h"
#include "../world/map.h"
#include "../physics/collision.h"
#include "../utils/vector.h"
#include "../core/state_manager.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct Game {
    bool is_running;

    // Window
    Renderer *renderer;
    Camera *camera;
    SDL_Window *window;

    // Input
    InputKeyboardState keyboard;
    Commands commands;

    // Entities
    AssetManager *asset_manager;
    Vector *entities;

    // World
    Map *map;
    SolidTileIDs solid_tile_ids;
    Vector *custom_colliders;
    Vector *scenery_elements;

    // Game States
    StateManager *state_manager;

    // Time Settings
    Uint64 frequency;
    Uint64 last_time;
    float accumulator;
    float delta_time;
} Game;

Game *game_create(void);
bool manage_window_init(Game *game, float camera_x, float camera_y, float dead_zone_percentage);
bool manage_entities_add(Game *game, Entity* entity);
bool manage_world_init(Game *game, const char *map_file, int tile_size, char *tile_ids, int tile_count, SDL_Color tile_color);
bool manage_world_colliders_add(Game *game, float x, float y, float width, float height);
bool manage_world_scenery_elements_add(Game *game, SceneryElement *scenery_element);
void game_destroy(Game *game);
void game_update(Game *game);
void game_draw(Game *game);
void game_loop(Game *game);
void game_run(Game *game);

#endif // GAME_H