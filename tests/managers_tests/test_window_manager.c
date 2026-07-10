#include "test_window_manager.h"
#include "../../src/managers/window_manager.h"
#include "../../src/graphics/camera.h"
#include "../../src/graphics/renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_init_window(void) {

    Camera *camera = NULL;
    Renderer *renderer = NULL;
    bool result = init_window(&camera, &renderer, 0, 0, 0.1);

    assert(result == true);
    assert(camera != NULL);
    assert(renderer != NULL);

    camera_destroy(camera);
    renderer_destroy(renderer);
    printf("test_init_window passed\n");
}