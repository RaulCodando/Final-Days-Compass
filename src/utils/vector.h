#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void **data;
    size_t capacity;
    size_t size;
} Vector;

Vector *vector_create(void);
void vector_destroy(Vector *vec);
bool vector_push(Vector *vec, void *element);
bool vector_insert(Vector *vec, void *element, size_t index);
bool vector_reserve(Vector *vec, size_t capacity);
void *vector_get(Vector *vec, size_t index);
bool vector_remove(Vector *vec, size_t index);

#endif // VECTOR_H