#ifndef CAMERA_H
#define CAMERA_H

typedef struct Camera {
    float x;
    float y;
    float dead_zone_percentage;
    int width;
    int height;
} Camera;

Camera *camera_create(float x, float y, float dead_zone_percentage, int width, int height);
void camera_update(Camera *camera, float target_x, float target_y, int target_w, int target_h, int map_w, int map_h);
void camera_destroy(Camera *camera);

#endif //CAMERA_H