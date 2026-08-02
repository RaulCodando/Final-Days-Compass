#include "commands.h"

static void init_single_command(Command *cmd, InputKey key) {
    cmd->key_binding = key;
    cmd->active = false;
    cmd->previous = false;
    cmd->triggered = false;
}

static void update_single_command(Command *cmd, InputKeyboardState *keyboard) {
    cmd->previous = cmd->active;
    cmd->active = keyboard_is_key_pressed(keyboard, cmd->key_binding);
    cmd->triggered = cmd->active && !cmd->previous;
}

static void stop_single_command(Command *cmd) {
    cmd->active = false;
    cmd->previous = false;
    cmd->triggered = false;
}

void commands_init(Commands *commands) {
    if (!commands) return;

    init_single_command(&commands->move_left, INPUT_KEY_LEFT);
    init_single_command(&commands->move_right, INPUT_KEY_RIGHT);
    init_single_command(&commands->move_up, INPUT_KEY_UP);
    init_single_command(&commands->move_down, INPUT_KEY_DOWN);
    init_single_command(&commands->quit_game, INPUT_KEY_ESCAPE);
    init_single_command(&commands->confirm, INPUT_KEY_ENTER);
}

void commands_update(Commands *commands, InputKeyboardState *keyboard) {
    if (!commands || !keyboard) return;

    update_single_command(&commands->quit_game, keyboard);
    update_single_command(&commands->confirm, keyboard);
    update_single_command(&commands->move_left, keyboard);
    update_single_command(&commands->move_right, keyboard);
    update_single_command(&commands->move_up, keyboard);
    update_single_command(&commands->move_down, keyboard);
}

void commands_stop(Commands *commands) {
    if (!commands) return;

    stop_single_command(&commands->move_left);
    stop_single_command(&commands->move_right);
    stop_single_command(&commands->move_up);
    stop_single_command(&commands->move_down);
    stop_single_command(&commands->quit_game);
    stop_single_command(&commands->confirm);
}