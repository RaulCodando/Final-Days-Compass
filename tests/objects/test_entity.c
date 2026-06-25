#include "test_entity.h"
#include <stdio.h>
#include <stdlib.h>

void print_entity(Entity *entity){
    int height = entity->base.sprite->height;
    int width = entity->base.sprite->width;
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printf("%c", entity->base.sprite->pixels[i * width + j]);
        }
        printf("\n");
    }

    printf("Entity ID: %d\n", entity->base.id);
    printf("Entity Health: %d\n", entity->health);
    printf("Entity Standard Attack: %d\n", entity->standard_attack);
    printf("Entity Speed: %f\n", entity->speed);
    printf("Entity X Position: %f\n", entity->x_pos);
    printf("Entity Y Position: %f\n", entity->y_pos);
}

void test_entity_create(){
    Sprite *sprite = sprite_create("tests/assets/test_sprite04.txt");
    if(sprite == NULL){
        printf("test_entity_create: FAILED\n");
        exit(1);
    }

    Entity *entity = entity_create(PLAYER, sprite, 100, 10, 1.0f, 0.0f, 0.0f);
    if(entity == NULL){
        printf("test_entity_create: FAILED\n");
        exit(1);
    }

    print_entity(entity);
    printf("test_entity_create: PASSED\n");
    entity_destroy(entity);
}