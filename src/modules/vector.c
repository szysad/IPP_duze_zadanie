/** @file
 * Implementacja struktury generycznego Vektora.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#include "vector.h"
#include <stdlib.h>
#include <assert.h>

static size_t const INITIAL_CAPACITY = 5;
static int const EXPANSION_RATIO = 2;

Vector *Vector_new(void (*freeFunc)(void *)) {
	Vector *v = malloc(sizeof(Vector));
	if(!v) {
		return NULL;
	}
	v->elementsArr = malloc(INITIAL_CAPACITY * sizeof(void *));
	if(!v->elementsArr) {
		return NULL;
	}
	v->size = 0;
	v->capacity = INITIAL_CAPACITY;
	v->freeFunc = freeFunc;
	return v;
}

void Vector_setFreeFunction(Vector *vector, void (*freeFunction)(void *)) {
	vector->freeFunc = freeFunction;
}

bool Vector_add(Vector *vector, void *element) {
	if(vector->size >= vector->capacity) {
		vector->elementsArr = realloc(vector->elementsArr, vector->capacity * EXPANSION_RATIO * sizeof(void *));
		vector->capacity *= EXPANSION_RATIO;
		if(!vector->elementsArr) {
			return false;
		}
	}
	vector->elementsArr[vector->size] = element;
	(vector->size)++;
	return true;
}

void *Vector_getElemById(Vector *vector, size_t id) {
	assert(id < vector->size);
	return vector->elementsArr[id];
}

static bool Vector_optimizeMemory(Vector *vector) {
	if(vector->size > INITIAL_CAPACITY * EXPANSION_RATIO && vector->size < vector->capacity / EXPANSION_RATIO) {
		vector->capacity /= EXPANSION_RATIO;
		vector->elementsArr = realloc(vector->elementsArr, vector->capacity * sizeof(void *));
		return true;
	}
	return false;
}

size_t Vector_getSize(Vector *v) {
	return v->size;
}

void Vector_removeElemByIndex(Vector *vector, size_t index) {
	assert(index < vector->size);
	if(vector->freeFunc != NULL) {
		vector->freeFunc(vector->elementsArr[index]);
	}
	for(size_t i = index; i < vector->size - 1; i++) {
		vector->elementsArr[i] = vector->elementsArr[i + 1];
	}
	(vector->size)--;
	Vector_optimizeMemory(vector);
}

void *Vector_extractElementById(Vector *vector, size_t id) {
	assert(id < vector->size);
	void *ElementToBeRemoved = vector->elementsArr[id];
	for(size_t i = id; i < vector->size - 1; i++) {
		vector->elementsArr[i] = vector->elementsArr[i + 1];
	}
	(vector->size)--;
	Vector_optimizeMemory(vector);

	return ElementToBeRemoved;
}

int Vector_getElementVectorIndex(Vector *vector, void *elem) {
	for(size_t i = 0; i < Vector_getSize(vector); i++) {
		if(Vector_getElemById(vector, i) == elem) {
			return i;
		}
	}
	return -1;
}

bool Vector_isEmpty(Vector *vector) {
	return (vector->size == 0);
}

void Vector_remove(Vector *v) {
	if (v->freeFunc != NULL) {
		for (size_t i = 0; i < v->size; i++) {
			v->freeFunc(v->elementsArr[i]);
		}
	}
	free(v->elementsArr);
	free(v);
}

bool Vector_removeElement(Vector *v, void *elem) {
	int elemIndex = Vector_getElementVectorIndex(v, elem);
	if(elemIndex == -1) {
		return false;
	}
	Vector_removeElemByIndex(v, elemIndex);
	return true;
}