#include "menu_state.h"
#include "../ui/hud.h"
#include "../ui/menu_hud.h"
#include "../core/game.h"
#include "../graphics/renderer.h"
#include <stdlib.h>

static void menu_state_enter(Game *game, void *state_data) {
    if (!game) return;

    MenuStateData *data = (MenuStateData *)state_data;
    if (data) {
        data->menu_hud = menu_hud_create();
        data->menu_state = MENU_NONE_SELECTED;
    }
}

static void menu_state_exit(Game *game, void *state_data) {
    if (!game || !state_data) return;

    MenuStateData *data = (MenuStateData *)state_data;
    if (!data->menu_hud) return;

    hud_destroy(data->menu_hud);
    data->menu_hud = NULL;
}

static void menu_state_update(Game *game, void *state_data) {
    if (!game || !state_data) return;

    MenuStateData *data = (MenuStateData *)state_data;

    if (game->commands.quit_game.triggered) {
        game->commands.quit_game.triggered = false;
        state_manager_pop(game->state_manager, game);
        return;
    }

    HudElement *menu_hud = data->menu_hud;
    if(!menu_hud) return;

    HudElement *btn_continue = menu_hud->data.container->children[0];
    HudElement *btn_exit     = menu_hud->data.container->children[1];

    switch (data->menu_state) {
        case MENU_NONE_SELECTED:
            if (game->commands.move_up.triggered || game->commands.move_down.triggered) {
                data->menu_state = MENU_PLAY_SELECTED;
            }
            break;

        case MENU_PLAY_SELECTED:
            hud_container_set_state(btn_continue, 1);
            hud_container_set_state(btn_exit, 0);

            if (game->commands.move_down.triggered) {
                data->menu_state = MENU_QUIT_SELECTED;
            }

            if (game->commands.confirm.triggered) {
                game->commands.confirm.triggered = false;
                state_manager_pop(game->state_manager, game);
                return;
            }
            break;

        case MENU_QUIT_SELECTED:
            hud_container_set_state(btn_continue, 0);
            hud_container_set_state(btn_exit, 1);

            if (game->commands.move_up.triggered) {
                data->menu_state = MENU_PLAY_SELECTED;
            }

            if (game->commands.confirm.triggered) {
                game->commands.confirm.triggered = false;
                game->is_running = false;
                return;
            }
            break;
    }

    game->commands.move_up.triggered = false;
    game->commands.move_down.triggered = false;
}

static void menu_state_render(Game *game, void *state_data) {
    if (!game || !state_data) return;

    MenuStateData *data = (MenuStateData *)state_data;
    if (!data->menu_hud) return;

    renderer_draw_hud_element(game->renderer, data->menu_hud);
}

GameState *menu_state_create() {
    GameState *state = (GameState *)malloc(sizeof(GameState));
    if (!state) return NULL;

    MenuStateData *data = (MenuStateData *)malloc(sizeof(MenuStateData));
    if (!data) {
        free(state);
        return NULL;
    }
    data->menu_state = MENU_NONE_SELECTED;

    state->type = STATE_MENU;
    state->update_lower_state = false;
    state->render_lower_state = true;
    state->enter = menu_state_enter;
    state->exit = menu_state_exit;
    state->update = menu_state_update;
    state->render = menu_state_render;
    state->state_data = data;
    
    return state;
}