#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "game_state.h"
#include "../ui/hud.h"

typedef enum MenuState {
    MENU_NONE_SELECTED,
    MENU_PLAY_SELECTED,
    MENU_QUIT_SELECTED
} MenuState;

typedef struct MenuStateData {
    MenuState menu_state;
    HudElement *menu_hud;
} MenuStateData;

GameState *menu_state_create();

#endif // MENU_STATE_H