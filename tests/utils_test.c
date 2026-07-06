#include "../src/utils/vector.h"
#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h>

void test_vector_create(){
    Vector *vector = vector_create();
    if(vector == NULL){
        printf("Vector creation failed.\n");
    }else{
        printf("Vector created successfully.\n");
    }
    vector_destroy(vector);
}

void test_vector_push(){
    Vector *vector = vector_create();
    int a = 1;
    int b = 2;
    int c = 3;
    vector_push(vector, &a);
    vector_push(vector, &b);
    vector_push(vector, &c);
    print_vector(vector);
    vector_destroy(vector);
}

void test_vector_remove(){
    Vector *vector = vector_create();
    int a = 1;
    int b = 2;
    int c = 3;
    vector_push(vector, &a);
    vector_push(vector, &b);
    vector_push(vector, &c);
    vector_remove(vector, 1);
    print_vector(vector);
    vector_destroy(vector);
}

void test_vector_insert(){
    Vector *vector = vector_create();
    int a = 1;
    int b = 2;
    int c = 3;
    vector_push(vector, &a);
    vector_push(vector, &b);
    vector_push(vector, &c);
    vector_insert(vector, &c, 1);
    print_vector(vector);
    vector_destroy(vector);
}

void test_vector_reserve(){
    Vector *vector = vector_create();
    int a = 1;
    int b = 2;
    int c = 3;
    vector_push(vector, &a);
    vector_push(vector, &b);
    vector_push(vector, &c);
    vector_reserve(vector, 10);
    print_vector(vector);
    printf("Vector capacity: %zu\n", vector->capacity);
    printf("Vector size: %zu\n", vector->size);
    vector_destroy(vector);
}

void test_vector_get(){
    Vector *vector = vector_create();
    int a = 1;
    int b = 2;
    int c = 3;
    vector_push(vector, &a);
    vector_push(vector, &b);
    vector_push(vector, &c);
    int *d = vector_get(vector, 1);
    printf("%d\n", *d);
    vector_destroy(vector);
}

int main(){
    test_vector_create();
    test_vector_push();
    test_vector_remove();
    test_vector_insert();
    test_vector_reserve();
    test_vector_get();

    return 0;
}