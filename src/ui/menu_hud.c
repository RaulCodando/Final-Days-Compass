#include "menu_hud.h"
#include "hud.h"
#include <stdlib.h>
#include "stdio.h"
#include "../graphics/sprite.h"
#include "../core/settings.h"

HudElement *menu_hud_create() {
    const char *sprite_paths01[1] = {"tests/assets/test_menu_hud_container_sprite.txt"};
    const char *sprite_paths02[2] = {
        "tests/assets/test_hud_container_sprite.txt",
        "tests/assets/test_hud_selected_container_sprite.txt"
    };

    HudElement *main_container = hud_create_container(sprite_paths01, 1, 0, 0, 40, 20, true, true);
    HudElement *button_container_01 = hud_create_container(sprite_paths02, 2, 0, 4, 34, 5, true, false);
    HudElement *button_container_02 = hud_create_container(sprite_paths02, 2, 0, 11, 34, 5, true, false);
    
    HudElement *button_text01 = hud_create_text("Continue", 0, 0, true, true);
    HudElement *button_text02 = hud_create_text("Exit", 0, 0, true, true);

    hud_container_add_child(main_container, button_container_01);
    hud_container_add_child(main_container, button_container_02);
    hud_container_add_child(button_container_01, button_text01);
    hud_container_add_child(button_container_02, button_text02);

    return main_container;
}