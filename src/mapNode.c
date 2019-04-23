#include "mapNode.h"
#include <stdio.h>

const int INITIAL_INDEX = -1;

MapNode *MapNode_new(City *city) {
	if(!city) {
		return NULL;
	}
	MapNode *mapNode = malloc(sizeof(MapNode));
	if(!mapNode) {
		return NULL;
	}
	mapNode->index = INITIAL_INDEX;
	mapNode->city = city;
	mapNode->roadVector = RoadVector_new();
	if(!mapNode->roadVector) {
		return NULL;
	}
	return mapNode;
}

void MapNode_remove(MapNode *mapNode) {
	City_remove(mapNode->city);
	RoadVector_remove(mapNode->roadVector);
	free(mapNode);
}

void MapNode_print(MapNode *mapNode) {
    printf("\t");
	printf("index: %d\n", mapNode->index);
	City_print(mapNode->city);
	RoadVector_print(mapNode->roadVector);
}