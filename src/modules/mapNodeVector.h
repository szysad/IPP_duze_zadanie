#ifndef __MAPNODEVECTOR_H__
#define __MAPNODEVECTOR_H__

#include "mapNode.h"

typedef struct _mapNodeVector {
	size_t size;
	size_t capacity;
	MapNode **mapNodeArray;
} MapNodeVector;


MapNodeVector *MapNodeVector_new();

bool MapNodeVector_add(MapNodeVector *vector, MapNode *mapNode, int *added_index);

void MapNodeVector_remove(MapNodeVector *vector);

size_t MapNodeVector_getSize(MapNodeVector *vector);

MapNode *MapNodeVector_getMapNodeById(MapNodeVector *vector, size_t id);

#endif //__MAPNODEVECTOR_H__
