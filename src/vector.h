#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    void **elementsArr;
    size_t capacity;
    size_t size;
    void (*freeFunc)(void *);
} Vector;

Vector *Vector_new(void (*freeFunc)(void *));

bool Vector_add(Vector *vector, void *element);

void Vector_remove(Vector *v);

void *Vector_getElemById(Vector *vector, size_t id);

void *Vector_extractElementById(Vector *vector, size_t id);

int Vector_getElementVectorIndex(Vector *vector, void *elem);

size_t Vector_getSize(Vector *v);

#endif //__VECTOR_H__
