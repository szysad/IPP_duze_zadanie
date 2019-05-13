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
    mapNode->oldestRoadAgeToMe = INT_MAX;
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
	printf("\tdistance from root: %d\n", mapNode->distanceFromRoot);
	printf("\tqueue index: %d\n", mapNode->queueIndex);
	printf("\toldest road age to me: %d\n", mapNode->oldestRoadAgeToMe);
	City_print(mapNode->city);
	RoadVector_print(mapNode->roadVector);
}

static MapNode *MapNode_getMoreBranchedMapNode(MapNode *node1, MapNode *node2) {
    if(RoadVector_getSize(node1->roadVector) < RoadVector_getSize(node2->roadVector)) {
        return node2;
    }
    else {
        return node1;
    }
}

static MapNode *MapNode_getLessBranchedMapNode(MapNode *node1, MapNode *node2) {
    if(RoadVector_getSize(node1->roadVector) < RoadVector_getSize(node2->roadVector)) {
        return node1;
    }
    else {
        return node2;
    }
}

long int min(int a, int b) {
    if(a < b) {
        return a;
    }
    else {
        return b;
    }
}

int MapNode_getNewNodeOldestRoadAge(MapNode *nodeFrom, Road *roadFromTo) {
    assert(roadFromTo->buildYear != 0);
    return min(roadFromTo->buildYear, nodeFrom->oldestRoadAgeToMe);
}

/* slightly faster then MapNode_getRoadFromConnectedNodes(), doesnt specify road direction */
bool MapNode_doesRoadExist(MapNode *node1, MapNode *node2) {
    MapNode *lessBranchedMapNode = MapNode_getLessBranchedMapNode(node1, node2);
    MapNode *moreBranchedMapNode = MapNode_getMoreBranchedMapNode(node1, node2);

    for(size_t i = 0; i < RoadVector_getSize(lessBranchedMapNode->roadVector); i++) {
        Road *checkedRoad = RoadVector_getRoadById(lessBranchedMapNode->roadVector, i);

        if(checkedRoad->destination_index == moreBranchedMapNode->index) {
            return true;
        }
    }
    return false;
}

Road *MapNode_getRoadFromConnectedNodes(MapNode *start, MapNode *target) {
    for(size_t i = 0; i < RoadVector_getSize(start->roadVector); i++) {
        Road *checkedRoad = RoadVector_getRoadById(start->roadVector, i);
        if(checkedRoad->destination_index == target->index) {
            return checkedRoad;
        }
    }
    return NULL;
}

void MapNode_setDistanceFromRoot(MapNode *mapNode, unsigned distance) {
    mapNode->distanceFromRoot = distance;
}

void MapNode_setQueueIndex(MapNode *mapNode, int index) {
    mapNode->queueIndex = index;
}

void MapNode_setOldestRoadAge(MapNode *mapNode, int age) {
    mapNode->oldestRoadAgeToMe = age;
}