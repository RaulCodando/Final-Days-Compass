#include "utils.h"
#include <stdio.h>

void print_sprite(Sprite *sprite){
    for(int i = 0; i < sprite->height; i++){
        for(int j = 0; j < sprite->width; j++){
            printf("%c", sprite->pixels[i * sprite->width + j]);
        }
        printf("\n");
    }
}

void print_vector(Vector *vector){
    for(int i = 0; i < vector->size; i++){
        printf("%d ", *(int*) vector->data[i]);
    }
    printf("\n");
}