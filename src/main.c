#include "map_dev.h"
#include "mapNodePriorityQueue.h"
#include <stdio.h>

int main() {

    Map *map = newMap();

    assert(addRoad(map, "1", "2", 10, 1)); //1
    assert(addRoad(map, "2", "3", 4, 2)); //1
    assert(addRoad(map, "3", "8", 5, 2)); //1
    assert(addRoad(map, "1", "4", 10, 1)); //2
    assert(addRoad(map, "4", "5", 4, 2)); //2
    assert(addRoad(map, "5", "8", 3, 1)); //2
    assert(addRoad(map, "1", "6", 10, 2)); //3
    assert(addRoad(map, "6", "7", 3, 2)); //3
    assert(addRoad(map, "7", "8", 5, 1)); //3

    assert(addRoad(map, "9", "10", 5, 1)); //erorr
    assert(addRoad(map, "7", "8", 5, 1)); //erorr


    printf("rezult: %d\n" ,newRoute(map, 421, "1", "9"));

    //Map_print(map);

    for(size_t i = 0; i < map->nationalRoadsVector->size; i++) {
        MapNodeList_print(map->nationalRoadsVector->elementsArr[i]);
        printf("----------\n");
    }

    deleteMap(map);

}