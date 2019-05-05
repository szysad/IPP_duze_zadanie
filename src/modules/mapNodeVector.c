#include <assert.h>
#include "mapNodeVector.h"

static const size_t INITIAL_CAPACITY = 10;
static const size_t EXPANSION_RATIO = 2;

MapNodeVector *MapNodeVector_new() {
	MapNodeVector *newVector = malloc(sizeof(MapNodeVector));
	newVector->size = 0;
	newVector->capacity = INITIAL_CAPACITY;
	newVector->mapNodeArray = malloc(INITIAL_CAPACITY * sizeof(MapNode*));

	return newVector;
}

bool MapNodeVector_add(MapNodeVector *vector, MapNode *mapNode, int *added_index) {
	if(vector->size >= vector->capacity) {
		vector-> mapNodeArray = realloc(vector->mapNodeArray, vector->capacity * EXPANSION_RATIO * sizeof(MapNode*));
		vector->capacity *= EXPANSION_RATIO;
		if(vector->mapNodeArray == NULL) {
			return false;
		}
	}
	vector->mapNodeArray[vector->size] = mapNode;
	*added_index = (int)vector->size;
	(vector->size)++;
	return true;
}

void MapNodeVector_remove(MapNodeVector *vector) {
	for(size_t i = 0; i < vector->size; i++) {
		MapNode_remove(vector->mapNodeArray[i]);
	}
	free(vector->mapNodeArray);
	free(vector);
}

static bool MapNodeVector_optimizeVectorMemory(MapNodeVector *vector) {
	if(vector->size > INITIAL_CAPACITY * EXPANSION_RATIO && vector->size < vector->capacity / EXPANSION_RATIO) {
		vector->capacity /= EXPANSION_RATIO;
		vector->mapNodeArray = realloc(vector->mapNodeArray, vector->capacity * sizeof(MapNode*));
		return true;
	}
	return false;
}

void MapNodeVector_removeMapNodeByIndex(MapNodeVector *vector, size_t index) {
	assert(index < vector->size);
	MapNode_remove(vector->mapNodeArray[index]);
	for(size_t i = index; i < vector->size - 1; i++) {
		vector->mapNodeArray[i] = vector->mapNodeArray[i + 1];
	}
	(vector->size)--;
	MapNodeVector_optimizeVectorMemory(vector);
}

size_t MapNodeVector_getSize(MapNodeVector *vector) {
	return vector->size;
}

MapNode *MapNodeVector_getMapNodeById(MapNodeVector *vector, size_t id) {
	assert(id < vector->size);
	return vector->mapNodeArray[id];
}

/* development */
void MapNodeVector_print(MapNodeVector *mapNodeVector) {
    for(size_t i = 0; i < MapNodeVector_getSize(mapNodeVector); i++) {
        printf("node %ld\n", i);
        MapNode_print(MapNodeVector_getMapNodeById(mapNodeVector, i));
    }
}
