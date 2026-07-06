#include "vector.h"

Vector *vector_create(void){
    Vector *vector = malloc(sizeof(Vector));
    if(vector == NULL) return NULL;

    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;

    return vector;
}


void vector_destroy(Vector *vector){
    if(vector == NULL) return;

    free(vector->data);
    free(vector);
}

bool vector_push(Vector *vector, void *element){
    if(vector == NULL) return false;

    if(vector->size == vector->capacity){
        size_t new_capacity = (vector->capacity == 0) ? 1 : vector->capacity * 2;
        void **new_data = realloc(vector->data, new_capacity * sizeof *vector->data);
        
        if(new_data == NULL) return false;

        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    vector->data[vector->size++] = element;
    return true;
}

bool vector_insert(Vector *vector, void *element, size_t index){
    if(vector == NULL || element == NULL || index > vector->size) return false;

    if(vector->size == vector->capacity){
        size_t new_capacity = (vector->capacity == 0) ? 1 : vector->capacity * 2;
        void **new_data = realloc(vector->data, new_capacity * sizeof *vector->data);
        
        if(new_data == NULL) return false;

        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    if(index < vector->size){
        for(size_t i = vector->size; i > index; i--){
            vector->data[i] = vector->data[i - 1];
        }
    }

    vector->data[index] = element;
    vector->size++;
    return true;
}

bool vector_reserve(Vector *vector, size_t capacity){
    if(vector == NULL) return false;
    if(capacity <= vector->capacity) return true;

    void **new_data = realloc(vector->data, capacity * sizeof *vector->data);
    if(new_data == NULL) return false;

    vector->data = new_data;
    vector->capacity = capacity;
    return true;
}

void *vector_get(Vector *vec, size_t index){
    if(vec == NULL) return NULL;
    if(index >= vec->size) return NULL;
    return vec->data[index];
}

bool vector_remove(Vector *vector, size_t index){
    if(vector == NULL || index >= vector->size) return false;

    if(index < vector->size - 1){
        for(size_t i = index; i < vector->size - 1; i++){
            vector->data[i] = vector->data[i + 1];
        }
    }

    vector->size--;
    return true;
}