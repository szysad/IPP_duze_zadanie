/** @file
 * Implementacja struktury Vektora węzłów struktury mapy krajowej.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

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

size_t MapNodeVector_getSize(MapNodeVector *vector) {
	return vector->size;
}

MapNode *MapNodeVector_getMapNodeById(MapNodeVector *vector, size_t id) {
	assert(id < vector->size);
	return vector->mapNodeArray[id];
}