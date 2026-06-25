#include "test_game_object.h"
#include <stdio.h>
#include <stdlib.h>

void print_object(GameObject *game_object){
    int height = game_object->sprite->height;
    int width = game_object->sprite->width;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printf("%c", game_object->sprite->pixels[i * width + j]);
        }
        printf("\n");
    }
}

void test_game_object_init(){
    Sprite *sprite = sprite_create("tests/assets/test_sprite04.txt");
    if(sprite == NULL){
        printf("test_game_object_init: FAILED\n");
        exit(1);
    }

    GameObject *game_object = (GameObject*)malloc(sizeof(GameObject));
    game_object_init(game_object, PLAYER, sprite);
    if(game_object->id != PLAYER){
        printf("test_game_object_init: FAILED\n");
        exit(1);
    }

    print_object(game_object);
    printf("test_game_object_init: PASSED\n");
    game_object_destroy(game_object);
}