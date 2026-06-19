#include "commands.h"

void commands_init(Commands *commands) {
    if (!commands) return;

    commands->move_left.key_binding = INPUT_KEY_LEFT;
    commands->move_right.key_binding = INPUT_KEY_RIGHT;
    commands->move_up.key_binding = INPUT_KEY_UP;
    commands->move_down.key_binding = INPUT_KEY_DOWN;
    commands->quit_game.key_binding = INPUT_KEY_ESCAPE;

    commands->move_left.active = false;
    commands->move_right.active = false;
    commands->move_up.active = false;
    commands->move_down.active = false;
    commands->quit_game.active = false;
}

void commands_update(Commands *commands, InputKeyboardState *keyboard) {
    if (!commands || !keyboard) return;

    commands->move_left.active  = keyboard_is_key_pressed(keyboard, commands->move_left.key_binding);
    commands->move_right.active = keyboard_is_key_pressed(keyboard, commands->move_right.key_binding);
    commands->move_up.active    = keyboard_is_key_pressed(keyboard, commands->move_up.key_binding);
    commands->move_down.active  = keyboard_is_key_pressed(keyboard, commands->move_down.key_binding);
    commands->quit_game.active  = keyboard_is_key_pressed(keyboard, commands->quit_game.key_binding);
}