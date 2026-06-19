#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>

typedef enum {
    INPUT_KEY_ESCAPE,
    INPUT_KEY_LEFT,
    INPUT_KEY_RIGHT,
    INPUT_KEY_UP,
    INPUT_KEY_DOWN,
    INPUT_KEY_COUNT
} InputKey;

typedef enum {
    KEY_STATE_RELEASED,
    KEY_STATE_PRESSED
} KeyState;

typedef struct {
    KeyState keys[INPUT_KEY_COUNT];
} InputKeyboardState;

void keyboard_init(InputKeyboardState *input);
bool keyboard_is_key_pressed(InputKeyboardState *input, InputKey key);
void keyboard_update(InputKeyboardState *input);

#endif