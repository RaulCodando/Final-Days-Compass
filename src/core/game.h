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
#include <stdbool.h>
#include <windows.h>

typedef struct Game{
    bool is_running;

    // Window
    Renderer *renderer;
    Camera *camera;

    // Input
    InputKeyboardState keyboard;
    Commands commands;

    // Entities
    AssetManager *asset_manager;
    Entity **entities;
    int entity_count;

    // World
    Map *map;
    SolidTileIDs solid_tile_ids;

    // Time Settings
    LARGE_INTEGER frequency;
    LARGE_INTEGER last_time;
    float accumulator;
    float delta_time;
} Game;

Game *game_create(void);
void game_init_window(Game *game, float camera_x, float camera_y, float dead_zone_percentage);
void game_init_entities(Game *game, Entity **entities, int entity_count);
void game_add_entity(Game *game, ObjectIDs id, Sprite *sprite, int health, int standard_attack, float speed, float x_pos, float y_pos);
void game_init_world(Game *game, const char *map_file, float tile_size, const char *tile_ids, int tile_count);
void game_destroy(Game *game);
void game_update(Game *game);
void game_draw(Game *game);
void game_loop(Game *game);
void game_run(Game *game);

#endif /* GAME_H */