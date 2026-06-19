#include "graphics/test_sprite.h"
#include "graphics/test_renderer.h"
#include "core/test_game.h"
#include "input/test_keyboard.h"
#include "input/test_commands.h"
#include <stdio.h>
#include <stdlib.h>

void ask_for_permission(){
    printf("\nTest completed. Proceed to the next test? (y/n): ");
    char response;
    scanf(" %c", &response);
    if(response != 'y' && response != 'Y'){
        exit(0);
    }
    system("cls");
}

int main(){
    test_sprite_create();
    ask_for_permission();
    test_renderer();
    ask_for_permission();
    test_keyboard();
    ask_for_permission();
    test_commands();
    ask_for_permission();
    test_game();
    return 0;
}