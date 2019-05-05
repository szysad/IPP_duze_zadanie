//
// Created by szysad on 05.05.19.
//

#ifndef DROGI_MAPNODEPRIORITYQUEUE_H
#define DROGI_MAPNODEPRIORITYQUEUE_H

#include "mapNode.h"


typedef struct {
    int size;
    int capacity;
    MapNode **arr;
} MapNodePriorityQueue;

MapNodePriorityQueue *MapNodePriorityQueue_new(int size);

void MapNodePriorityQueue_remove(MapNodePriorityQueue *queue);

void MapNodePriorityQueue_add(MapNodePriorityQueue *queue, MapNode *mapNode);

void MapNodePriorityQueue_updateNode(MapNodePriorityQueue *queue, MapNode *mapNode, int val);

MapNode *MapNodePriorityQueue_popMin(MapNodePriorityQueue *queue);

bool MapNodePriorityQueue_isEmpty(MapNodePriorityQueue *queue);

#endif //DROGI_MAPNODEPRIORITYQUEUE_H
