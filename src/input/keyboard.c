#include "keyboard.h"
#include <windows.h>

static const int WINDOWS_VK_MAPPING[INPUT_KEY_COUNT] = { 
    VK_ESCAPE,
    VK_LEFT,
    VK_RIGHT,
    VK_UP,
    VK_DOWN,
    VK_RETURN
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

void keyboard_update(InputKeyboardState *input){
    if(!input) return;

    for(int i = 0; i < INPUT_KEY_COUNT; i++){
        int vk_code = WINDOWS_VK_MAPPING[i];

        if(GetAsyncKeyState(vk_code) & 0x8000){
            input->keys[i] = KEY_STATE_PRESSED;
        }
        else{
            input->keys[i] = KEY_STATE_RELEASED;
        }
    }
}