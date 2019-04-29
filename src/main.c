#include "map_dev.h"
#include "mapNodePriorityQueue.h"
#include <stdio.h>

int main() {

    Map *map = newMap();

    assert(addRoad(map, "1", "2", 1, 1)); //1
    assert(addRoad(map, "2", "3", 4, 2)); //1
    assert(addRoad(map, "10", "9", 1, 1)); //1
    assert(addRoad(map, "10", "8", 5, 10)); //1
    assert(addRoad(map, "1", "8", 5, 1)); //1
    assert(addRoad(map, "3", "9", 3, 1)); //1


    assert(newRoute(map, 421, "1", "10"));

    printf("extend: %d\n", extendRoute(map, 421, "8"));


    //MapNodeList_print((MapNodeList*)Vector_getElemById(map->nationalRoadsVector, 0));
    //MapNodeList_print((MapNodeList*)Vector_getElemById(map->nationalRoadsVector, 0));

    //Map_print(map);

    //printf("%d\n", extendRoute(map, 421, "3"));

    for(size_t i = 0; i < map->nationalRoadsVector->size; i++) {
        MapNodeList_print(map->nationalRoadsVector->elementsArr[i]);
        printf("----------\n");
    }

    deleteMap(map);

}