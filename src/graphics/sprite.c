#include "sprite.h"
#include <stdio.h>
#include <stdlib.h>
#include "../core/settings.h"

Sprite *sprite_create(char *path){
    FILE *file = fopen(path, "rb");
    if (file == NULL){
        fprintf(stderr, "Error: Could not open file %s\n", path);
        return NULL;
    }

    char line[256];

    int width = 0;
    int height = 0;

    if(fgets(line, sizeof(line), file) != NULL){
        if(sscanf(line, "%d %d", &width, &height) != 2){
            fprintf(stderr, "Error: Invalid file format.\n");
            fclose(file);
            return NULL;
        }
    }

    if(width <=0 || height <=0){
        fprintf(stderr, "Error: Invalid dimensions.\n");
        fclose(file);
        return NULL;
    }

    Sprite *sprite = (Sprite*) malloc(sizeof(Sprite));
    if(sprite == NULL){
        fprintf(stderr, "Error: memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    sprite->height = height;
    sprite->width = width;
    size_t size = (size_t)width * (size_t)height;
    
    sprite->pixels = (char*) malloc(size * sizeof(char));
    if(sprite->pixels == NULL){
        fprintf(stderr, "Error: memory allocation failed for pixels\n");
        free(sprite);
        fclose(file);
        return NULL;
    }

    for (int y = 0; y < height; y++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            fprintf(stderr, "Error: Unexpected end of file.\n");
            free(sprite->pixels);
            free(sprite);
            fclose(file);
            return NULL;
        }

        int real_length = 0;
        while(line[real_length] != '\0' && line[real_length] != '\n' && line[real_length] != '\r'){
            real_length++;
        }

        for (int x = 0; x < width; x++) {
            if(x < real_length){
                sprite->pixels[y * width + x] = line[x];
            }
            else{
                sprite->pixels[y * width + x] = BLANK_CHARACTER;
            }
        }
    }

    fclose(file);
    return sprite;
}

Sprite *sprite_create_blank(int width, int height){
    if(width <=0 || height <=0){
        fprintf(stderr, "Error: Invalid dimensions.\n");
        return NULL;
    }

    Sprite *sprite = (Sprite*) malloc(sizeof(Sprite));
    if(sprite == NULL){
        fprintf(stderr, "Error: memory allocation failed.\n");
        return NULL;
    }

    sprite->height = height;
    sprite->width = width;
    size_t size = (size_t)width * (size_t)height;
    
    sprite->pixels = (char*) malloc(size * sizeof(char));
    if(sprite->pixels == NULL){
        fprintf(stderr, "Error: memory allocation failed for pixels\n");
        free(sprite);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        sprite->pixels[i] = BLANK_CHARACTER;
    }

    return sprite;
}

void sprite_destroy(Sprite *sprite){
    if(sprite != NULL){
        free(sprite->pixels);
        free(sprite);
    }
}