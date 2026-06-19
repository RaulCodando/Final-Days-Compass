#include "test_keyboard.h"
#include "../../src/input/keyboard.h"
#include <assert.h>
#include <windows.h>
#include <stdio.h>

void test_keyboard_init(){
    InputKeyboardState input;
    keyboard_init(&input);
    
    for(int i = 0; i < INPUT_KEY_COUNT; i++){
        assert(input.keys[i] == KEY_STATE_RELEASED);
    }

    printf("test_keyboard_init passed\n");
}

void test_keyboard_is_key_pressed(){
    InputKeyboardState mock_input;
    
    mock_input.keys[INPUT_KEY_LEFT] = KEY_STATE_PRESSED;
    mock_input.keys[INPUT_KEY_RIGHT] = KEY_STATE_RELEASED;

    assert(keyboard_is_key_pressed(&mock_input, INPUT_KEY_LEFT) == true);
    assert(keyboard_is_key_pressed(&mock_input, INPUT_KEY_RIGHT) == false);

    printf("test_keyboard_is_key_pressed passed\n");
}

void test_keyboard_update(){
    InputKeyboardState input;
    keyboard_init(&input);

    printf("test_keyboard_update started\n");
    printf("Press the 'Esc' key to continue\n");
    
    while(input.keys[INPUT_KEY_ESCAPE] != KEY_STATE_PRESSED){
        keyboard_update(&input);

        printf("\rLeft: %s | Right: %s | Up: %s | Down: %s    ",
            keyboard_is_key_pressed(&input, INPUT_KEY_LEFT) ? "PRESS" : "RELEASED",
            keyboard_is_key_pressed(&input, INPUT_KEY_RIGHT) ? "PRESS" : "RELEASED",
            keyboard_is_key_pressed(&input, INPUT_KEY_UP) ? "PRESS" : "RELEASED",
            keyboard_is_key_pressed(&input, INPUT_KEY_DOWN) ? "PRESS" : "RELEASED"
        );

        Sleep(30);
    }

    printf("test_keyboard_update passed\n");
}

void test_keyboard(){
    test_keyboard_init();
    test_keyboard_is_key_pressed();
    test_keyboard_update();
    printf("test_keyboard passed\n");
}