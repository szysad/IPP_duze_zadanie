#ifndef __MAPNODE_H__
#define __MAPNODE_H__

#include "roadVector.h"
#include "city.h"

typedef struct _mapNode {
	int index;
	City *city;
	RoadVector *roadVector;
	/* below are used for path finding algorithm */
	int distanceFromRoot;
	int queueIndex;
	int oldestRoadAgeToMe;
} MapNode;


MapNode *MapNode_new(City *city);

void MapNode_remove(MapNode *mapNode);

void MapNode_setDistanceFromRoot(MapNode *mapNode, int distance);

void MapNode_setQueueIndex(MapNode *mapNode, int index);

void MapNode_setOldestRoadAge(MapNode *mapNode, int age);

/* development */
void MapNode_print(MapNode *mapNode);

#endif //__MAPNODE_H__
