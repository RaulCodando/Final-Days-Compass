#include "keyboard.h"
#include <SDL3/SDL.h>

static const SDL_Scancode SDL_KEY_MAPPING[INPUT_KEY_COUNT] = { 
    SDL_SCANCODE_ESCAPE,
    SDL_SCANCODE_LEFT,
    SDL_SCANCODE_RIGHT,
    SDL_SCANCODE_UP,
    SDL_SCANCODE_DOWN,
    SDL_SCANCODE_RETURN
};

void keyboard_init(InputKeyboardState *input) {
    for (int i = 0; i < INPUT_KEY_COUNT; i++) {
        input->keys[i] = KEY_STATE_RELEASED;
    }
}

bool keyboard_is_key_pressed(InputKeyboardState *input, InputKey key){
    if(!input || key >= INPUT_KEY_COUNT || key < 0){
        return false;
    }
    return input->keys[key] == KEY_STATE_PRESSED;
}

void keyboard_update(InputKeyboardState *input) {
    if (!input) return;

    const bool *state = SDL_GetKeyboardState(NULL);
    if (!state) return;

    for (int i = 0; i < INPUT_KEY_COUNT; i++) {
        SDL_Scancode scancode = SDL_KEY_MAPPING[i];

        if (state[scancode]) {
            input->keys[i] = KEY_STATE_PRESSED;
        } else {
            input->keys[i] = KEY_STATE_RELEASED;
        }
    }
}