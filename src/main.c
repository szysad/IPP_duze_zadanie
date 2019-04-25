#include "map_dev.h"
#include "mapNodePriorityQueue.h"
#include <stdio.h>

int main() {

    Map *map = newMap();

    assert(addRoad(map, "1", "2", 10, 3));
    assert(addRoad(map, "1", "3", 10, 1));
    assert(addRoad(map, "3", "2", 10, 5));
    assert(addRoad(map, "3", "4", 10, 4));
    assert(addRoad(map, "2", "4", 10, 2));
    assert(addRoad(map, "3", "5", 10, 3));
    assert(addRoad(map, "4", "5", 10, 1));
    assert(addRoad(map, "2", "5", 10, 3));

    assert(newRoute(map, 420, "1", "3"));

    Map_print(map);

    deleteMap(map);

}