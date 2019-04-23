#ifndef __MAPNODE_H__
#define __MAPNODE_H__

#include "roadVector.h"
#include "city.h"

typedef struct _mapNode {
	int index;
	City *city;
	RoadVector *roadVector;
} MapNode;


MapNode *MapNode_new(City *city);

void MapNode_remove(MapNode *mapNode);

/* development */
void MapNode_print(MapNode *mapNode);

#endif //__MAPNODE_H__
