#include "../../src/graphics/sprite.h"
#include "test_sprite.h"
#include <stdio.h>

void print_sprite(Sprite *sprite){
    for(int i = 0; i < sprite->height; i++){
        for(int j = 0; j < sprite->width; j++){
            printf("%c", sprite->pixels[i * sprite->width + j]);
        }
        printf("\n");
    }
}

void test_sprite_create(){
    Sprite *sprite = sprite_create("tests/assets/test_sprite01.txt");
    if(sprite == NULL){
        printf("Error: Could not create sprite.\n");
        return;
    }

    if(sprite->width != 7 || sprite->height != 7){
        printf("Error: Invalid sprite dimensions.\n");
        return;
    }

    if(sprite->pixels == NULL){
        printf("Error: Invalid sprite pixels.\n");
        return;
    }

    print_sprite(sprite);
    printf("Sprite created successfully.\n");
}