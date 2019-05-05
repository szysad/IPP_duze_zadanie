//
// Created by szysad on 05.05.19.
//

#include "mapNodePriorityQueue.h"

MapNodePriorityQueue *MapNodePriorityQueue_new(int size) {
    MapNodePriorityQueue *new = malloc(sizeof(MapNodePriorityQueue));
    new->arr = malloc(size * sizeof(MapNode*));
    for(int i = 0; i < size; i++) {
        new->arr[i] = NULL;
    }
    new->size = 0;
    new->capacity = size;
    return new;
}

void MapNodePriorityQueue_remove(MapNodePriorityQueue *queue) {
    free(queue->arr);
    free(queue);
}

void MapNodePriorityQueue_add(MapNodePriorityQueue *queue, MapNode *mapNode) {
    for(int i = 0; i < queue->capacity; i++) {
        if(queue->arr[i] == NULL) {
            queue->arr[i] = mapNode;
            (queue->size)++;
            return;
        }
    }
    assert(1 == 0);
}

void MapNodePriorityQueue_updateNode(MapNodePriorityQueue *queue, MapNode *mapNode, int val) {
    assert(queue->size > 0);
    mapNode->distanceFromRoot = val;
}

MapNode *MapNodePriorityQueue_popMin(MapNodePriorityQueue *queue) {
    assert(queue->size > 0);
    int min = INT_MAX;
    int index = -1;
    for(int i = 0; i < queue->capacity; i++) {
        if(queue->arr[i] != NULL && queue->arr[i]->distanceFromRoot <= min) {
            min = queue->arr[i]->distanceFromRoot;
            index = i;
        }
    }
    assert(index != -1);
    MapNode *pop = queue->arr[index];
    queue->arr[index] = NULL;
    (queue->size)--;
    return pop;
}

bool MapNodePriorityQueue_isEmpty(MapNodePriorityQueue *queue) {
    return queue->size == 0;
}