#include "map_dev.h"
#include "mapNodePriorityQueue.h"
#include "mapNode_list.h"
#include <string.h>
#include <assert.h>

Map* newMap(void) {
	Map *map = malloc(sizeof(Map));
	map->mapNodeVector = MapNodeVector_new();
	map->nationalRoadsVector = Vector_new(MapNodeList_remove);

	return map;
}

void deleteMap(Map *map) {
	MapNodeVector_remove(map->mapNodeVector);
	Vector_remove(map->nationalRoadsVector);
	free(map);
}

static MapNode *Map_doesCityExist(Map *map, const char *name) {
	for(size_t i = 0; i < MapNodeVector_getSize(map->mapNodeVector); i++) {
		MapNode *checkedMapNode = MapNodeVector_getMapNodeById(map->mapNodeVector, i);
		if(strcmp(checkedMapNode->city->name, name) == 0) {
			return checkedMapNode;
		}
	}
	return NULL;
}

static bool MapNode_connectMapNodes(MapNode *node1, MapNode *node2, size_t road_length, int road_builtYear) {
	bool flag = true;
	Road *road1to2 = Road_new(road_length, road_builtYear, node2->index);
	Road *road2to1 = Road_new(road_length, road_builtYear, node1->index);

	flag = road1to2 && road2to1;

	flag = flag && RoadVector_add(node1->roadVector, road1to2);
	flag = flag && RoadVector_add(node2->roadVector, road2to1);

	return flag;
}

static bool Map_addMapNode(Map *map, MapNode *mapNode) {
	bool flag = true;

	flag = MapNodeVector_add(map->mapNodeVector, mapNode, &(mapNode->index));
	assert(mapNode->index != -1);
	return flag;
}

bool addRoad(Map *map, const char *city_name1, const char *city_name2, unsigned length, int builtYear) {
    if(!Road_areParamsValid(length, builtYear)) {
        return false;
    }
    if(!City_isNameValid(city_name1) || !City_isNameValid(city_name2) || City_areNamesEqual(city_name1, city_name2)) {
        return false;
    }
	MapNode *mapNode1 = Map_doesCityExist(map, city_name1);
	MapNode *mapNode2 = Map_doesCityExist(map, city_name2);

	/* Both cities exist */
	if(mapNode1 && mapNode2) {
		if(MapNode_doesRoadExist(mapNode1, mapNode2)) {
			return false;
		}
		else {
			return MapNode_connectMapNodes(mapNode1, mapNode2, length, builtYear);
		}
	}
	/* Both cities do not exist */
	else if(!mapNode1 && !mapNode2) {
	    bool flag = true;
		MapNode *newMapNode1 = MapNode_new(City_new(city_name1));
		MapNode *newMapNode2 = MapNode_new(City_new(city_name2));

		flag = newMapNode1 && newMapNode2;

		if(flag) {
		    flag = Map_addMapNode(map, newMapNode1);
		    flag = flag && Map_addMapNode(map, newMapNode2);
            /* This assertion fails only if, OS cant provide more memory.
             * Currently program can not remove MapNodes, so it's fatal err */
		    assert(flag);
		}

		if(flag) {
		    flag = MapNode_connectMapNodes(newMapNode1, newMapNode2, length, builtYear);
		}

        /* if error occurred, free memory for already allocated nodes */
		if(!flag) {
            if(!newMapNode1 || !newMapNode2) {
                if(newMapNode1) {
                    MapNode_remove(newMapNode1);
                }
                if(newMapNode2) {
                    MapNode_remove(newMapNode2);
                }
                return false;
            }
		}
		return true;
	}
	/* One city exists, one does not */
	else {
		bool flag = true;
		if(mapNode1) {
			MapNode *newMapNode = MapNode_new(City_new(city_name2));
			flag = newMapNode;
			if(flag) {
				flag = Map_addMapNode(map, newMapNode);
                /* line 110 comment */
				assert(flag);
			}
			if(flag) {
				flag = MapNode_connectMapNodes(mapNode1, newMapNode, length, builtYear);
			}
		}
		else if(mapNode2){
			MapNode *newMapNode = MapNode_new(City_new(city_name1));
			flag = newMapNode;
			if(flag) {
				flag = Map_addMapNode(map, newMapNode);
                /* line 110 comment */
				assert(flag);
			}
			if(flag) {
				flag = MapNode_connectMapNodes(mapNode2, newMapNode, length, builtYear);
			}
		}
        return flag;
	}
}

bool repairRoad(Map *map, const char *city1, const char *city2, int repairYear) {
    /* 1 is valid road length */
    if(!Road_areParamsValid(1, repairYear)) {
        return false;
    }
    if(!City_isNameValid(city1) || !City_isNameValid(city2)) {
        return false;
    }

    MapNode *mapNode1 = Map_doesCityExist(map, city1);
    MapNode *mapNode2 = Map_doesCityExist(map, city2);

    if(!mapNode1 || !mapNode2) {
        return false;
    }

    Road *road1to2 = MapNode_getRoadFromConnectedNodes(mapNode1, mapNode2);
    Road *road2to1 = MapNode_getRoadFromConnectedNodes(mapNode2, mapNode1);

    if(!road1to2 || !road2to1) {
        return false;
    }

    Road_setAge(road1to2, repairYear);
    Road_setAge(road2to1, repairYear);

    return true;
}

static bool updateNodeOldestRoadAge(MapNode *nodeFrom, MapNode *nodeTo, Road *roadFromTo) {
    int newOldestRoadAgeVal = min(nodeTo->oldestRoadAgeToMe, MapNode_getNewNodeOldestRoadAge(nodeFrom, roadFromTo));

    if(newOldestRoadAgeVal < nodeTo->oldestRoadAgeToMe) {
        MapNode_setOldestRoadAge(nodeTo, newOldestRoadAgeVal);
        return true;
    }
    else {
        return false;
    }
}

static bool dijkstra(Map *map, MapNode *start, MapNode *end, int parentIndex[]) {

    MapNodePriorityQueue *queue = MapNodePriorityQueue_new();

    for(size_t i = 0; i < MapNodeVector_getSize(map->mapNodeVector); i++) {
        MapNode_setDistanceFromRoot(MapNodeVector_getMapNodeById(map->mapNodeVector, i), INT_MAX);
        MapNodePriorityQueue_add(queue, MapNodeVector_getMapNodeById(map->mapNodeVector, i));
        MapNode_setOldestRoadAge(MapNodeVector_getMapNodeById(map->mapNodeVector, i), INT_MAX);
        parentIndex[i] = -1;
    }

    MapNodePriorityQueue_updateNode(queue, start, 0);
    MapNode *processedNode = NULL;
    bool isFound = false;
    bool isExplicit = true;

    while ( !MapNodePriorityQueue_isEmpty(queue) && !isFound) {
        processedNode = MapNodePriorityQueue_popMin(queue);

        if(processedNode != NULL && processedNode->distanceFromRoot != INT_MAX && processedNode == end) {
            isFound = true;
        }

        if(processedNode != NULL && processedNode->distanceFromRoot != INT_MAX) {

            for (size_t i = 0; i < RoadVector_getSize(processedNode->roadVector) && processedNode != end; i++) {
                Road *currentRoad = RoadVector_getRoadById(processedNode->roadVector, i);
                int roadTarget = currentRoad->destination_index;
                MapNode *currentNode = MapNodeVector_getMapNodeById(map->mapNodeVector, roadTarget);
                int newDistance = processedNode->distanceFromRoot + currentRoad->length;

                if (currentNode->distanceFromRoot >= newDistance) {
                    int newAge = MapNode_getNewNodeOldestRoadAge(processedNode, currentRoad);
                    if(currentNode == end) {
                        if(newAge < end->oldestRoadAgeToMe) {
                            isExplicit = true;
                        }
                        if(newAge == end->oldestRoadAgeToMe) {
                            isExplicit = false;
                        }
                    }
                    if(currentNode->distanceFromRoot > newDistance) {
                        parentIndex[currentNode->index] = processedNode->index;
                        updateNodeOldestRoadAge(processedNode, currentNode, currentRoad);
                        MapNodePriorityQueue_updateNode(queue, currentNode, newDistance);
                    }
                    if(currentNode->distanceFromRoot == newDistance && min(newAge, currentNode->oldestRoadAgeToMe) < currentNode->oldestRoadAgeToMe) {
                        updateNodeOldestRoadAge(processedNode, currentNode, currentRoad);
                        parentIndex[currentNode->index] = processedNode->index;
                    }
                }
            }
        }
    }
    MapNodePriorityQueue_remove(queue);

    return isFound && isExplicit;
}

static MapNodeList *getRoutedById(Vector *vector, size_t id) {
    for(size_t i = 0; i < Vector_getSize(vector); i++) {
        MapNodeList *route = (MapNodeList*) Vector_getElemById(vector, i);
        if(route->routeId == id) {
            return route;
        }
    }
    return NULL;
}

static bool ParentIndexToList(Map *map, int parent[], int j, MapNodeList *list) {

    if(parent[j] == -1) {
        return true;
    }

    ParentIndexToList(map, parent, parent[j], list);

    if(!MapNodeList_append(list, MapNodeVector_getMapNodeById(map->mapNodeVector, j))){
        return false;
    }

    return true;
}

static MapNodeList *getNewRoute(Map *map, unsigned routeId, MapNode *start, MapNode *end) {
    int parentIndex[MapNodeVector_getSize(map->mapNodeVector)];

    if (!dijkstra(map, start, end, parentIndex)) {
        return NULL;
    }

    MapNodeList *roadList = MapNodeList_new(routeId);
    MapNodeList_setLength(roadList, end->distanceFromRoot);
    MapNodeList_setOldestIncludedRoadAge(roadList, end->oldestRoadAgeToMe);
    MapNodeList_append(roadList, start);

    if(!ParentIndexToList(map, parentIndex, end->index, roadList)) {
        MapNodeList_remove(roadList);
        return NULL;
    }

    return roadList;
}

bool newRoute(Map *map, unsigned routeId, const char *city1, const char *city2) {
    if (!map || !City_isNameValid(city1) || !City_isNameValid(city2) || City_areNamesEqual(city1, city2)) {
        return false;
    }
    if(!isRouteIdValid(routeId) || getRoutedById(map->nationalRoadsVector, routeId)) {
        return false;
    }

    MapNode *start = Map_doesCityExist(map, city1);
    MapNode *end = Map_doesCityExist(map, city2);

    if (!start || !end) {
        return false;
    }

    MapNodeList *newRoute = getNewRoute(map, routeId, start, end);

    if(!newRoute) {
        return false;
    }

    Vector_add(map->nationalRoadsVector, newRoute);

    return true;
}

bool extendRoute(Map *map, unsigned routeId, const char *city) {
    if(!map || !City_isNameValid(city) || !isRouteIdValid(routeId)) {
        return false;
    }
    MapNode *nodeToBeAdded = Map_doesCityExist(map, city);
    if(!nodeToBeAdded) {
        return false;
    }
    MapNodeList *mainRoute = getRoutedById(map->nationalRoadsVector, routeId);
    if(!mainRoute) {
        return false;
    }
    if(MapNodeList_isNodeIncludedInList(mainRoute, nodeToBeAdded)) {
        return false;
    }

    MapNodeList *routeAttachcedToStart = getNewRoute(map, routeId, nodeToBeAdded, MapNodeList_getHeadNode(mainRoute));
    if(!routeAttachcedToStart) {
        return false;
    }
    MapNodeList *routeAttachcedToEnd = getNewRoute(map, routeId, MapNodeList_getTailNode(mainRoute), nodeToBeAdded);
    if(!routeAttachcedToEnd) {
        return false;
    }

    int preference = MapNodeList_comparePreferenceOfRoutes(routeAttachcedToStart, routeAttachcedToEnd);
    int mainRouteIndexInVector = Vector_getElementVectorIndex(map->nationalRoadsVector, mainRoute);
    mainRoute = Vector_extractElementById(map->nationalRoadsVector, mainRouteIndexInVector);

    MapNodeList *newRoute = NULL;
    if(preference > 0) {
        newRoute = MapNodeList_mergeRoutes(routeAttachcedToStart, mainRoute, mainRoute->routeId);
        MapNodeList_remove(routeAttachcedToEnd);
    }
    else if(preference < 0) {
        newRoute = MapNodeList_mergeRoutes(mainRoute, routeAttachcedToEnd, mainRoute->routeId);
        MapNodeList_remove(routeAttachcedToStart);
    }
    else {
        MapNodeList_remove(routeAttachcedToStart);
        MapNodeList_remove(routeAttachcedToEnd);
        return false;
    }
    Vector_add(map->nationalRoadsVector, newRoute);

    return true;
}

void Map_print(Map *map) {
    MapNodeVector_print(map->mapNodeVector);
}