#include "menu_hud.h"
#include "hud.h"
#include <stdlib.h>
#include "stdio.h"
#include "../graphics/sprite.h"
#include "../core/settings.h"

HudElement *menu_hud_create(SDL_Renderer *renderer, TTF_Font *font) {
    SpriteSheet *hud_container_spritesheet = sprite_sheet_create(renderer, "assets/sprites/hud_sprites/hud_container_spritesheet.png", 136, 120);
    SpriteSheet *menu_hud_container_spritesheet = sprite_sheet_create(renderer, "assets/sprites/hud_sprites/menu_hud_container_sprite.png", 160, 80);

    Sprite *hud_container_sprite = sprite_create_from_sheet(hud_container_spritesheet, 136, 120);
    Sprite *menu_hud_container_sprite = sprite_create_from_sheet(menu_hud_container_spritesheet, 160, 80);
    

    HudElement *main_container = hud_create_container(renderer, menu_hud_container_sprite, 0, 0, 40, 20, true, true);
    HudElement *button_container_01 = hud_create_container(renderer, hud_container_sprite, 0, 16, 34, 5, true, false);
    HudElement *button_container_02 = hud_create_container(renderer, hud_container_sprite, 0, 44, 34, 5, true, false);
    
    HudElement *button_text01 = hud_create_text("Continue", 0, 0, true, true, font);
    HudElement *button_text02 = hud_create_text("Exit", 0, 0, true, true, font);

    hud_container_add_child(main_container, button_container_01);
    hud_container_add_child(main_container, button_container_02);
    hud_container_add_child(button_container_01, button_text01);
    hud_container_add_child(button_container_02, button_text02);

    return main_container;
}