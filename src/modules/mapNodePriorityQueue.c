/** @file
 * Implementacja struktury kolejki priorytetowej węzła struktury mapy krajowej.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */


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
	if(queue->size == 0) {
		assert(false);
	}
	mapNode->distanceFromRoot = val;
}

MapNode *MapNodePriorityQueue_popMin(MapNodePriorityQueue *queue) {
	assert(queue->size > 0);
	unsigned min = UINT_MAX;
	int index = -1;
	int last_age = INT_MIN;
	for(int i = 0; i < queue->capacity; i++) {
		if(queue->arr[i] != NULL && queue->arr[i]->distanceFromRoot <= min) {
			if(queue->arr[i]->distanceFromRoot < min) {
				min = queue->arr[i]->distanceFromRoot;
				index = i;
				if(queue->arr[i]->oldestRoadAgeToMe >= last_age) {
					last_age = queue->arr[i]->oldestRoadAgeToMe;
				}
			}
			else if(queue->arr[i]->distanceFromRoot == min && queue->arr[i]->oldestRoadAgeToMe >= last_age) {
				index = i;
				last_age = queue->arr[i]->oldestRoadAgeToMe;
				min = queue->arr[i]->distanceFromRoot;
			}
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