#ifndef GAME_H
#define GAME_H

#include "../graphics/renderer.h"
#include "../graphics/camera.h"
#include "../input/commands.h"
#include "../objects/asset_manager.h"
#include "../input/keyboard.h"
#include <stdbool.h>
#include <windows.h>

typedef struct Game{
    bool is_running;
    Renderer *renderer;
    Camera *camera;
    AssetManager *asset_manager;
    InputKeyboardState keyboard;
    Commands commands;
    LARGE_INTEGER frequency;
    LARGE_INTEGER last_time;
    float delta_time;
} Game;

Game *game_create(void);
void game_destroy(Game *game);
void game_update(Game *game);
void game_draw(Game *game);
void game_loop(Game *game);
void game_run(Game *game);

#endif /* GAME_H */