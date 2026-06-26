#include "camera.h"
#include <stdlib.h>
#include <stdio.h>

Camera *camera_create(float x, float y, float dead_zone_percentage, int width, int height){
    Camera *camera = (Camera*)malloc(sizeof(Camera));
    if (camera == NULL){
        fprintf(stderr, "Erro ao alocar memoria para a camera\n");
        return NULL;
    }

    camera->x = x;
    camera->y = y;
    camera->dead_zone_percentage = dead_zone_percentage;
    camera->width = width;
    camera->height = height;
    return camera;
}

void camera_update(Camera *camera, float target_x, float target_y, int target_w, int target_h, int map_w, int map_h){
    if (camera == NULL){
        fprintf(stderr, "Erro: Camera invalida no update\n");
        return;
    }

    float cam_w = (float) camera->width;
    float cam_h = (float) camera->height;

    float dead_zone_margin_x = cam_w * camera->dead_zone_percentage;
    float dead_zone_margin_y = cam_h * camera->dead_zone_percentage;

    float player_screen_x = target_x - camera->x;
    float player_screen_y = target_y - camera->y;

    if(player_screen_x + (float) target_w >= cam_w - dead_zone_margin_x){
        camera->x = target_x + (float) target_w - (cam_w - dead_zone_margin_x);
    }
    else if(player_screen_x <= dead_zone_margin_x){
        camera->x = target_x - dead_zone_margin_x;
    }

    if(player_screen_y + (float) target_h >= cam_h - dead_zone_margin_y){
        camera->y = target_y + (float) target_h - (cam_h - dead_zone_margin_y);
    }
    else if(player_screen_y <= dead_zone_margin_y){
        camera->y = target_y - dead_zone_margin_y;
    }

    if(camera->x < 0) camera->x = 0.f;
    if(camera->y < 0) camera->y = 0.f;
    
    float max_x = (float)map_w - cam_w;
    float max_y = (float)map_h - cam_h;

    if (camera->x > max_x) camera->x = max_x;
    if (camera->y > max_y) camera->y = max_y;
}

void camera_destroy(Camera *camera){
    if (camera != NULL){
        free(camera);
    }
}