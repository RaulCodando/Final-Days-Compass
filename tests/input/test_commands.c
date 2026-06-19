#include "test_commands.h"
#include <stdio.h>
#include <windows.h>
#include <assert.h>

void test_commands_init(){
    Commands commands;
    commands_init(&commands);
    assert(commands.move_left.key_binding == INPUT_KEY_LEFT);
    assert(commands.move_right.key_binding == INPUT_KEY_RIGHT);
    assert(commands.move_up.key_binding == INPUT_KEY_UP);
    assert(commands.move_down.key_binding == INPUT_KEY_DOWN);
    assert(commands.quit_game.key_binding == INPUT_KEY_ESCAPE);
    assert(commands.move_left.active == false);
    assert(commands.move_right.active == false);
    assert(commands.move_up.active == false);
    assert(commands.move_down.active == false);
    assert(commands.quit_game.active == false);
}

void test_commands_update(){
    Commands commands;
    commands_init(&commands);
    InputKeyboardState keyboard;
    keyboard_init(&keyboard);
    
    commands_update(&commands, &keyboard);

    printf("test_commands_update started\n");
    printf("Press the 'Esc' key to continue\n");
    
    while(!commands.quit_game.active){
        keyboard_update(&keyboard);
        commands_update(&commands, &keyboard);
        
        printf("\rMove Left: %s | Move Right: %s | Move Up: %s | Move Down: %s | Quit Game: %s    ",
            commands.move_left.active ? "ACTIVE" : "INACTIVE",
            commands.move_right.active ? "ACTIVE" : "INACTIVE",
            commands.move_up.active    ? "ACTIVE" : "INACTIVE",
            commands.move_down.active  ? "ACTIVE" : "INACTIVE",
            commands.quit_game.active  ? "ACTIVE" : "INACTIVE"
        );
        
        Sleep(10); 
    }
    printf("\ntest_commands_update finished successfully!\n");
}

void test_commands(){
    test_commands_init();
    test_commands_update();
}