#ifndef COMMANDS_H
#define COMMANDS_H

#include "keyboard.h"

typedef struct{
    bool active;
    bool previous;
    bool triggered;
    InputKey key_binding;
} Command;

typedef struct{
    Command move_left;
    Command move_right;
    Command move_up;
    Command move_down;
    Command quit_game;
    Command confirm;
} Commands;

void commands_init(Commands *commands);
void commands_update(Commands *commands, InputKeyboardState *kayboard);
void commands_stop(Commands *commands);

#endif
