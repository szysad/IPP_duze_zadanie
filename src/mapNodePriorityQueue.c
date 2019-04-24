#include "mapNodePriorityQueue.h"

#include <stdlib.h>

const int INITIAL_CAPACITY = 5;
const int EXPANSION_RATIO = 2;


MapNodePriorityQueue *MapNodePriorityQueue_new() {
	MapNodePriorityQueue *newPQueue = malloc(sizeof(MapNodePriorityQueue));
	if(!newPQueue) {
		return NULL;
	}
	newPQueue->mapNodesArr = malloc(INITIAL_CAPACITY * sizeof(MapNode*));
	if(!newPQueue->mapNodesArr) {
		return NULL;
	}
	newPQueue->capacity = INITIAL_CAPACITY;
	newPQueue->size = 0;

	return newPQueue;
}

void MapNodePriorityQueue_remove(MapNodePriorityQueue *queue) {
	free(queue->mapNodesArr);
	free(queue);
}

static void swapNodesByIndex(MapNode **mapNodeArr, int index1, int index2) {
    printf("i1 = %d\n", mapNodeArr[index1]->queueIndex);
    printf("i2 = %d\n", mapNodeArr[index2]->queueIndex);
    MapNode_setQueueIndex(mapNodeArr[index1], index2);
    MapNode_setQueueIndex(mapNodeArr[index2], index1);
	MapNode *tmp = mapNodeArr[index1];
	mapNodeArr[index1] = mapNodeArr[index2];
	mapNodeArr[index2] = tmp;
    printf("i1 = %d\n", mapNodeArr[index1]->queueIndex);
    printf("i2 = %d\n", mapNodeArr[index2]->queueIndex);
    printf("\n");
}

static int parent(int i) {
	return (i - 1) / 2;
}

static int lChild(int i) {
	return (i * 2) + 1;
}

static int rChild(int i) {
	return (i * 2) + 2;
}

static void MapNodePriorityQueue_bubbleUp(MapNodePriorityQueue *queue, int index) {
    while (index > 0 && queue->mapNodesArr[parent(index)]->distanceFromRoot > queue->mapNodesArr[index]->distanceFromRoot) {
        swapNodesByIndex(queue->mapNodesArr, index, parent(index));
        index = parent(index);
    }
}

bool MapNodePriorityQueue_add(MapNodePriorityQueue *queue, MapNode *mapNode) {
	if(queue->size == queue->capacity) {
		queue->mapNodesArr = realloc(queue->mapNodesArr ,queue->capacity * EXPANSION_RATIO * sizeof(MapNode*));
		if(!queue->mapNodesArr) {
			return false;
		}
		queue->capacity *= EXPANSION_RATIO;
	}

	int i = queue->size;
	queue->mapNodesArr[i] = mapNode;
	MapNode_setQueueIndex(queue->mapNodesArr[i], i);
	(queue->size)++;

	MapNodePriorityQueue_bubbleUp(queue, i);

	return true;
}

static void MapNodePriorityQueue_bubbleDown(MapNodePriorityQueue *queue, int index) {
	while ( (lChild(index) < queue->size && queue->mapNodesArr[lChild(index)]->distanceFromRoot < queue->mapNodesArr[index]->distanceFromRoot) ||
			(rChild(index) < queue->size && queue->mapNodesArr[rChild(index)]->distanceFromRoot < queue->mapNodesArr[index]->distanceFromRoot) ) {

		if(rChild(index) < queue->size) {
			/* node can swap with both lchild and rchild */
			printf("can go lchild or rchild\n");
			if(queue->mapNodesArr[lChild(index)]->distanceFromRoot < queue->mapNodesArr[rChild(index)]->distanceFromRoot) {
				/* lchild has bigger priority then rchild */
				swapNodesByIndex(queue->mapNodesArr, index, lChild(index));
				index = lChild(index);
			} else {
			  /* rchild has bigger priority then lchild */
			    swapNodesByIndex(queue->mapNodesArr, index, rChild(index));
				index = rChild(index);
			}
		} else {
			printf("can go lchild only\n");
			/* node can only swap with lchild */
			swapNodesByIndex(queue->mapNodesArr, index, lChild(index));
			index = lChild(index);
		}
	}
}

void MapNodePriorityQueue_changeKey(MapNodePriorityQueue *queue, int index, int val) {
	if(val > queue->mapNodesArr[index]->distanceFromRoot) {
		MapNode_setDistanceFromRoot(queue->mapNodesArr[index], val);
		MapNodePriorityQueue_bubbleDown(queue, index);
	}
	if(val < queue->mapNodesArr[index]->distanceFromRoot) {
		MapNode_setDistanceFromRoot(queue->mapNodesArr[index], val);
		MapNodePriorityQueue_bubbleUp(queue, index);
	}
}



/* DEVELOPMENT */
void MapNodePriorityQueue_print(MapNodePriorityQueue *queue) {
	for(int i = 0; i < queue->size; i++) {
		MapNode_print(queue->mapNodesArr[i]);
	}
}