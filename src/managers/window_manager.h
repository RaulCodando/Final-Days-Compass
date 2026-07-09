#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <stdbool.h>

typedef struct Camera Camera;
typedef struct Renderer Renderer;

bool init_window(Camera **camera, Renderer **renderer, float camera_x, float camera_y, float dead_zone_percentage);

#endif /* WINDOW_MANAGER_H */