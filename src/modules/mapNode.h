#ifndef __MAPNODE_H__
#define __MAPNODE_H__

#include "roadVector.h"
#include "city.h"

typedef struct _mapNode {
	int index;
	City *city;
	RoadVector *roadVector;
	/* below are used for path finding algorithm */
    unsigned distanceFromRoot;
	int queueIndex;
	int oldestRoadAgeToMe;
} MapNode;


MapNode *MapNode_new(City *city);

long int min(int a, int b);

void MapNode_remove(MapNode *mapNode);

void MapNode_setDistanceFromRoot(MapNode *mapNode, unsigned distance);

void MapNode_setQueueIndex(MapNode *mapNode, int index);

void MapNode_setOldestRoadAge(MapNode *mapNode, int age);

bool MapNode_doesRoadExist(MapNode *node1, MapNode *node2);

Road *MapNode_getRoadFromConnectedNodes(MapNode *start, MapNode *target);

int MapNode_getNewNodeOldestRoadAge(MapNode *nodeFrom, Road *roadFromTo);

/* development */
void MapNode_print(MapNode *mapNode);

#endif //__MAPNODE_H__
