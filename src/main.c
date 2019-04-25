#include "map_dev.h"
#include "mapNodePriorityQueue.h"
#include <stdio.h>

int main() {

    MapNodePriorityQueue *h = MapNodePriorityQueue_new();

    MapNode *mapNodes[10];
    for(int i = 0; i < 10; i++) {
        mapNodes[i] = MapNode_new(City_new("elo"));
    }

    for(int i = 0; i < 10; i++) {
        MapNodePriorityQueue_add(h, mapNodes[i]);
    }

    for(int i = 0; i < h->size; i++) {
        MapNodePriorityQueue_updateNode(h, mapNodes[i], (i*i*i + 5*i - 6)/(10 % (i+1)+1));
    }

    MapNodePriorityQueue_print(h);

    while (!MapNodePriorityQueue_isEmpty(h)) {
        MapNode_print(MapNodePriorityQueue_popMin(h));
    }

    MapNodePriorityQueue_print(h);

    for(int i = 0; i < 10; i++) {
        MapNode_remove(mapNodes[i]);
    }

    MapNodePriorityQueue_remove(h);

}