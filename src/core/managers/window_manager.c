#include "window_manager.h"
#include "../../graphics/renderer.h"
#include "../../graphics/camera.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>

bool init_window(Camera **camera, Renderer **renderer, float camera_x, float camera_y, float dead_zone_percentage){
    if(!camera || !renderer) return false;
    
    *camera = camera_create(camera_x, camera_y, dead_zone_percentage, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(*camera == NULL){ 
        printf("Failed to create camera\n");
        return false;
    }
    
    *renderer = renderer_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(*renderer == NULL){
        camera_destroy(*camera);
        *camera = NULL;
        printf("Failed to create renderer\n");
        return false;
    }

    return true;
}