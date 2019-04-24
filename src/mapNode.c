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
    mapNode->distanceFromRoot = INITIAL_INDEX;
    mapNode->queueIndex = INITIAL_INDEX;
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
	printf("\tindex: %d\n", mapNode->index);
	printf("\troot from distance: %d\n", mapNode->distanceFromRoot);
	printf("\tqueue index: %d\n", mapNode->queueIndex);
	City_print(mapNode->city);
	RoadVector_print(mapNode->roadVector);
}

void MapNode_setDistanceFromRoot(MapNode *mapNode, int distance) {
    mapNode->distanceFromRoot = distance;
}

void MapNode_setQueueIndex(MapNode *mapNode, int index) {
    mapNode->queueIndex = index;
}