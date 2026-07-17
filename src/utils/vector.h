#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Vector {
    void **data;
    size_t capacity;
    size_t size;
} Vector;

typedef void (*destroy_data_func)(void *data);

Vector *vector_create(void);
void vector_destroy(Vector *vector, destroy_data_func destroy_data);
bool vector_push(Vector *vector, void *element);
bool vector_insert(Vector *vector, void *element, size_t index);
bool vector_reserve(Vector *vector, size_t capacity);
void *vector_get(Vector *vector, size_t index);
bool vector_remove(Vector *vector, size_t index);

#endif // VECTOR_H