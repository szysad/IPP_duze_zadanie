/** @file
 * Implementacja struktury Vektora dróg w strukturze mapy.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */


#include <stdbool.h>
#include <assert.h>
#include "roadVector.h"
#include "road.h"

#include <stdio.h>

static const size_t INITIAL_CAPACITY = 3;
static const size_t EXPANSION_RATIO = 2;

RoadVector *RoadVector_new() {
	RoadVector *newVector = malloc(sizeof(RoadVector));
	if(newVector == NULL) {
		return NULL;
	}
	newVector->size = 0;
	newVector->capacity = INITIAL_CAPACITY;
	newVector->roadArray = malloc(INITIAL_CAPACITY * sizeof(Road*));

	return newVector;
}

bool RoadVector_add(RoadVector *vector, Road *road) {
	assert(vector);
	if(vector->size >= vector->capacity) {
		vector->roadArray = realloc(vector->roadArray, vector->capacity * EXPANSION_RATIO * sizeof(Road*));
		vector->capacity *= EXPANSION_RATIO;
		if(vector->roadArray == NULL) {
			return false;
		}
	}
	vector->roadArray[vector->size] = road;
	(vector->size)++;
	return true;
}

static bool RoadVector_optimizeVectorMemory(RoadVector *vector) {
	if(vector->size > INITIAL_CAPACITY * EXPANSION_RATIO && vector->size < vector->capacity / EXPANSION_RATIO) {
		vector->capacity /= EXPANSION_RATIO;
		vector->roadArray = realloc(vector->roadArray, vector->capacity * sizeof(Road*));
		return true;
	}
	return false;
}

void RoadVector_removeRoadByIndex(RoadVector *vector, size_t index) {
	assert(index < vector->size);
	free(vector->roadArray[index]);
	for(size_t i = index; i < vector->size - 1; i++) {
		vector->roadArray[i] = vector->roadArray[i + 1];
	}
	(vector->size)--;
	RoadVector_optimizeVectorMemory(vector);
}

void RoadVector_remove(RoadVector *vector) {
	for(size_t i = 0; i < vector->size; i++) {
		Road_remove(vector->roadArray[i]);
	}
	free(vector->roadArray);
	free(vector);
}

size_t RoadVector_getSize(RoadVector *vector) {
	return vector->size;
}

Road *RoadVector_getRoadById(RoadVector *vector, size_t id) {
	assert(id < vector->size);
	return vector->roadArray[id];
}

int RoadVector_getRoadIndexInVector(RoadVector *vector, Road *road) {
	for(size_t i = 0; i < RoadVector_getSize(vector); i++) {
		if(road == RoadVector_getRoadById(vector, i)) {
			return i;
		}
	}
	return -1;
}