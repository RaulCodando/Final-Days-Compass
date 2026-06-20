#ifndef COMMANDS_H
#define COMMANDS_H

#include "keyboard.h"

typedef struct{
    bool active;
    InputKey key_binding;
} Command;

typedef struct{
    Command move_left;
    Command move_right;
    Command move_up;
    Command move_down;
    Command quit_game;
} Commands;

void commands_init();
void commands_update(Commands *commands, InputKeyboardState *kayboard);

#endif
