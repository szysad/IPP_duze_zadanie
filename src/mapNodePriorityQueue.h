#ifndef __MAPNODEPRIORITYQUEUE_H__
#define __MAPNODEPRIORITYQUEUE_H__

#include "mapNode.h"


typedef struct _heap {
    int capacity;
    int size;
    MapNode **mapNodesArr;
} MapNodePriorityQueue;

MapNodePriorityQueue *MapNodePriorityQueue_new(void);

void MapNodePriorityQueue_remove(MapNodePriorityQueue *queue);

bool MapNodePriorityQueue_add(MapNodePriorityQueue *queue, MapNode *mapNode);

void MapNodePriorityQueue_updateNode(MapNodePriorityQueue *queue, MapNode *mapNode, int val);

void MapNodePriorityQueue_removeNode(MapNodePriorityQueue *queue, MapNode *mapNode);

MapNode *MapNodePriorityQueue_popMin(MapNodePriorityQueue *queue);

bool MapNodePriorityQueue_isEmpty(MapNodePriorityQueue *queue);

/* DEVELOPMENT */
void MapNodePriorityQueue_print(MapNodePriorityQueue *queue);

#endif //__MAPNODEPRIORITYQUEUE_H__
