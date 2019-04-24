#ifndef __MAPNODEPRIORITYQUEUE_H__
#define __MAPNODEPRIORITYQUEUE_H__

#include "mapNode.h"


typedef struct _heap {
    int capacity;
    int size;
    MapNode **mapNodesArr;
} MapNodePriorityQueue;

MapNodePriorityQueue *MapNodePriorityQueue_new();

void MapNodePriorityQueue_remove(MapNodePriorityQueue *queue);

bool MapNodePriorityQueue_add(MapNodePriorityQueue *queue, MapNode *mapNode);

void MapNodePriorityQueue_changeKey(MapNodePriorityQueue *queue, int index, int val);

/* DEVELOPMENT */
void MapNodePriorityQueue_print(MapNodePriorityQueue *queue);

#endif //__MAPNODEPRIORITYQUEUE_H__
