#include "commands.h"

void commands_init(Commands *commands) {
    if (!commands) return;

    commands->move_left.key_binding = INPUT_KEY_LEFT;
    commands->move_right.key_binding = INPUT_KEY_RIGHT;
    commands->move_up.key_binding = INPUT_KEY_UP;
    commands->move_down.key_binding = INPUT_KEY_DOWN;
    commands->quit_game.key_binding = INPUT_KEY_ESCAPE;
    commands->confirm.key_binding = INPUT_KEY_ENTER;

    commands->move_left.active = false;
    commands->move_right.active = false;
    commands->move_up.active = false;
    commands->move_down.active = false;
    commands->quit_game.active = false;
    commands->confirm.active = false;
}

void commands_update(Commands *commands, InputKeyboardState *keyboard) {
    if (!commands || !keyboard) return;

    commands->quit_game.previous = commands->quit_game.active;
    commands->quit_game.active  = keyboard_is_key_pressed(keyboard, commands->quit_game.key_binding);
    commands->quit_game.triggered = commands->quit_game.active && !commands->quit_game.previous;

    commands->confirm.previous = commands->confirm.active;
    commands->confirm.active  = keyboard_is_key_pressed(keyboard, commands->confirm.key_binding);
    commands->confirm.triggered = commands->confirm.active && !commands->confirm.previous;

    commands->move_left.previous = commands->move_left.active;
    commands->move_left.active  = keyboard_is_key_pressed(keyboard, commands->move_left.key_binding);
    commands->move_left.triggered = commands->move_left.active && !commands->move_left.previous;

    commands->move_right.previous = commands->move_right.active;
    commands->move_right.active = keyboard_is_key_pressed(keyboard, commands->move_right.key_binding);
    commands->move_right.triggered = commands->move_right.active && !commands->move_right.previous;

    commands->move_up.previous = commands->move_up.active;
    commands->move_up.active = keyboard_is_key_pressed(keyboard, commands->move_up.key_binding);
    commands->move_up.triggered = commands->move_up.active && !commands->move_up.previous;

    commands->move_down.previous = commands->move_down.active;
    commands->move_down.active = keyboard_is_key_pressed(keyboard, commands->move_down.key_binding);
    commands->move_down.triggered = commands->move_down.active && !commands->move_down.previous;
}

void commands_stop(Commands *commands){
    if(!commands) return;

    commands->move_left.active = false;
    commands->move_left.triggered = false;

    commands->move_right.active = false;
    commands->move_right.triggered = false;

    commands->move_up.active = false;
    commands->move_up.triggered = false;

    commands->move_down.active = false;
    commands->move_down.triggered = false;

    commands->quit_game.active = false;
    commands->quit_game.triggered = false;

    commands->confirm.active = false;
    commands->confirm.triggered = false;
}