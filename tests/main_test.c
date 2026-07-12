#include "graphics_tests/test_sprite.h"
#include "graphics_tests/test_renderer.h"
#include "core_tests/test_game.h"
#include "input_tests/test_keyboard.h"
#include "input_tests/test_commands.h"
#include "world_tests/test_tiles.h"
#include "objects_tests/test_game_object.h"
#include "objects_tests/test_entity.h"
#include "objects_tests/test_asset_manager.h"
#include "world_tests/test_map.h"
#include "graphics_tests/test_camera.h"
#include "physics_tests/test_collision.h"
#include "managers_tests/test_window_manager.h"
#include "managers_tests/test_entity_manager.h"
#include "managers_tests/test_world_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void choose_test(){
    printf("Which test do you want to do?: \n");
    printf("1. Sprite\n");
    printf("2. Tileset\n");
    printf("3. Map\n");
    printf("4. Camera\n");
    printf("5. Renderer\n");
    printf("6. Keyboard\n");
    printf("7. Commands\n");
    printf("8. Game Object\n");
    printf("9. Collision\n");
    printf("10. Entity\n");
    printf("11. Asset Manager\n");
    printf("12. Window Manager\n");
    printf("13. Entity Manager\n");
    printf("14. World Manager\n");
    printf("15. Game\n");
    int choice;
    scanf(" %d", &choice);
    system("cls");
    switch(choice){
        case 1:
            test_sprite();
            break;
        case 2:
            test_tileset();
            break;
        case 3:
            test_map();
            break;
        case 4:
            test_camera();
            break;
        case 5:
            test_renderer();
            break;
        case 6:
            test_keyboard();
            break;
        case 7:
            test_commands();
            break;
        case 8:
            test_game_object_init();
            break;
        case 9:
            test_collision();
            break;
        case 10:
            test_entity();
            break;
        case 11:
            test_asset_manager();
            break;
        case 12:
            test_init_window();
            break;
        case 13:
            test_entity_manager();
            break;
        case 14:
            test_world_manager();
            break;
        case 15:
            test_game();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

bool ask_for_permission(){
    printf("\nTest completed. Do you wish to do another test? (y/n): ");
    char response;
    scanf(" %c", &response);
    
    if(response != 'y' && response != 'Y'){
        return false;
    }
    
    system("cls");
    return true;
}

int main(){
    bool permission = false;
    
    printf("\nDo you wish to start a test? (y/n): ");
    char response;
    scanf(" %c", &response);
    
    if(response == 'y' || response == 'Y'){
        permission = true;
    }

    while(permission){
        choose_test();
        permission = ask_for_permission();
        system("cls");
    }

    printf("All tests completed successfully.\n");
    return 0;
}