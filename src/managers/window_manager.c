#include "window_manager.h"
#include "../graphics/renderer.h"
#include "../graphics/camera.h"
#include "../core/settings.h"
#include "../core/settings.h"
#include <stdio.h>
#include <stdlib.h>

bool init_window(Camera **camera, Renderer **renderer, SDL_Window **window, float camera_x, float camera_y, float dead_zone_percentage) {
    if (!camera || !renderer || !window) return false;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erro ao inicializar SDL: %s\n", SDL_GetError());
        return  false;
    }
    
    *window = SDL_CreateWindow("Game", SCREEN_WIDTH * RENDER_SCALE, SCREEN_HEIGHT * RENDER_SCALE, SDL_WINDOW_FULLSCREEN);
    if (*window == NULL) { 
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    *camera = camera_create(camera_x, camera_y, dead_zone_percentage, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (*camera == NULL) { 
        fprintf(stderr, "Failed to create camera\n");
        SDL_DestroyWindow(*window);
        *window = NULL;
        return false;
    }
    
    *renderer = renderer_create(*window, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (*renderer == NULL) {
        fprintf(stderr, "Failed to create renderer\n");
        camera_destroy(*camera);
        *camera = NULL;
        SDL_DestroyWindow(*window);
        *window = NULL;
        return false;
    }

    return true;
}