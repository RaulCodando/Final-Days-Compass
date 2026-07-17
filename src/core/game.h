#ifndef GAME_H
#define GAME_H

#include "../graphics/renderer.h"
#include "../graphics/camera.h"
#include "../input/commands.h"
#include "../objects/asset_manager.h"
#include "../input/keyboard.h"
#include "../objects/entity.h"
#include "../world/map.h"
#include "../physics/collision.h"
#include "../utils/vector.h"
#include "../core/state_manager.h"
#include <stdbool.h>
#include <windows.h>

typedef struct Game {
    bool is_running;

    // Window
    Renderer *renderer;
    Camera *camera;

    // Input
    InputKeyboardState keyboard;
    Commands commands;

    // Entities
    AssetManager *asset_manager;
    Vector *entities;
    int entity_count;

    // World
    Map *map;
    SolidTileIDs solid_tile_ids;
    Vector *custom_colliders;

    // Game States
    StateManager *state_manager;

    // Time Settings
    LARGE_INTEGER frequency;
    LARGE_INTEGER last_time;
    float accumulator;
    float delta_time;
} Game;

typedef void (*behavior_update)(Entity* self, Game *game_context);

Game *game_create(void);
bool manage_window_init(Game *game, float camera_x, float camera_y, float dead_zone_percentage);
bool manage_entities_init(Game *game, ObjectIDs *object_ids, const char **sprite_paths, int sprite_count);
bool manage_entities_add(Game *game, ObjectIDs id, int health, int standard_attack, float speed, float x_pos, float y_pos, const char *sprite_path);
bool manage_entities_add_behavior(Game *game, ObjectIDs id, behavior_update behavior);
bool manage_entities_init_collider(Game *game, ObjectIDs id, float collider_width, float collider_height, float offset_x, float offset_y);
bool manage_world_init(Game *game, const char *map_file, int tile_size, char *tile_ids, int tile_count);
bool manage_world_colliders_init(Game *game);
bool manage_world_colliders_add(Game *game, float x, float y, float width, float height);
void game_destroy(Game *game);
void game_update(Game *game);
void game_draw(Game *game);
void game_loop(Game *game);
void game_run(Game *game);

#endif // GAME_H