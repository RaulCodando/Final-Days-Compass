#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Vector {
    void **data;
    size_t capacity;
    size_t size;
} Vector;

Vector *vector_create(void);
void vector_destroy(Vector *vector);
bool vector_push(Vector *vector, void *element);
bool vector_insert(Vector *vector, void *element, size_t index);
bool vector_reserve(Vector *vector, size_t capacity);
void *vector_get(Vector *vector, size_t index);
bool vector_remove(Vector *vector, size_t index);

#endif // VECTOR_H