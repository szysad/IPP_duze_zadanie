#include "map.h"
#include "mapNodePriorityQueue.h"
#include <stdio.h>

int main() {

    Map *map = newMap();

    /*
    assert(addRoad(map, "1", "2", 1, 1)); //1
    assert(addRoad(map, "2", "3", 2, 2)); //1
    assert(addRoad(map, "10", "9", 3, 3)); //1
    assert(addRoad(map, "10", "8", 4, 4)); //1
    assert(addRoad(map, "1", "8", 5, 5)); //1
    assert(addRoad(map, "3", "9", 6, 6)); //1
    */

    assert(addRoad(map, "1", "2", 1, 1));
    assert(addRoad(map, "2", "3", 1, 2));
    assert(addRoad(map, "3", "1", 10, 3));
    assert(addRoad(map, "4", "1", 10, 4));

    assert(newRoute(map, 421, "3", "4"));

    char const *str = getRouteDescription(map, 421);
    printf(str);

    deleteMap(map);

}