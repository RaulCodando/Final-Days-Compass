#include "test_camera.h"
#include "../src/graphics/camera.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define EPSILON 0.0001f

void test_camera_create(){
    Camera *camera = camera_create(10.0f, 20.0f, 0.25f, 32, 24);
    assert(camera != NULL);
    assert(fabs(camera->x - 10.0f) < EPSILON);
    assert(fabs(camera->y - 20.0f) < EPSILON);
    assert(fabs(camera->dead_zone_percentage - 0.25f) < EPSILON);
    assert(camera->width == 32);
    assert(camera->height == 24);
    camera_destroy(camera);
    printf("test_camera_create passed.\n");
}

void test_camera_update(){
    Camera *camera = camera_create(0.0f, 0.0f, 0.25f, 16, 16);
    assert(camera != NULL);
    
    camera_update(camera, 0.0f, 0.0f, 4, 4, 100, 100);

    assert(fabs(camera->x - 0.0f) < EPSILON);
    assert(fabs(camera->y - 0.0f) < EPSILON);

    camera_update(camera, 15.0f, 15.0f, 4, 4, 100, 100);
    assert(camera->x > 0.0f);
    assert(camera->y > 0.0f);
    assert(camera->x <= (float)100 - (float)16);
    assert(camera->y <= (float)100 - (float)16);

    camera_destroy(camera);
    printf("test_camera_update passed.\n");
}

void test_camera(){
    test_camera_create();
    test_camera_update();
}