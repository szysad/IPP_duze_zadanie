/** @file
* Implementacja klasy przechowującej mapę dróg krajowych.
*
* @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
* @copyright Uniwersytet Warszawski
* @date 20.03.2019
*/

#include "map.h"
#include "modules/mapNodePriorityQueue.h"
#include "modules/mapNode_list.h"
#include "modules/vector.h"
#include <string.h>
#include <assert.h>

Map* newMap(void) {
	Map *map = malloc(sizeof(Map));
	if(map == NULL) {
        return NULL;
	}
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

static bool MapNode_connectMapNodes(MapNode *node1, MapNode *node2, unsigned road_length, int road_builtYear) {
	bool flag;
	Road *road1to2 = Road_new(road_length, road_builtYear, node2->index);
	Road *road2to1 = Road_new(road_length, road_builtYear, node1->index);

	flag = road1to2 && road2to1;

	flag = flag && RoadVector_add(node1->roadVector, road1to2);
	flag = flag && RoadVector_add(node2->roadVector, road2to1);

	return flag;
}

static void MapNode_disconnectNodes(MapNode *node1, MapNode *node2) {
    Road *road1to2 = MapNode_getRoadFromConnectedNodes(node1, node2);
    Road *road2to1 = MapNode_getRoadFromConnectedNodes(node2, node1);
    assert(road1to2 && road2to1);

    int road1to2VectorIndex =  RoadVector_getRoadIndexInVector(node1->roadVector, road1to2);
    int road2to1VectorIndex =  RoadVector_getRoadIndexInVector(node2->roadVector, road2to1);

    assert(road1to2VectorIndex >= 0 && road2to1VectorIndex >= 0);

    RoadVector_removeRoadByIndex(node1->roadVector, road1to2VectorIndex);
    RoadVector_removeRoadByIndex(node2->roadVector, road2to1VectorIndex);
}

static bool Map_addMapNode(Map *map, MapNode *mapNode) {
	bool flag;

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
	    bool flag;
		MapNode *newMapNode1 = MapNode_new(City_new(city_name1));
		MapNode *newMapNode2 = MapNode_new(City_new(city_name2));

		flag = newMapNode1 && newMapNode2;

		if(flag) {
		    flag = Map_addMapNode(map, newMapNode1);
		    flag = flag && Map_addMapNode(map, newMapNode2);
            /* This assertion fails only if, OS cant provide more memory.
             * Currently program can not removetmp MapNodes, so it's fatal err */
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

    if(road1to2 == NULL || road2to1 == NULL) {
        return false;
    }

    if(Road_getAge(road1to2) > repairYear) {
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

    MapNodePriorityQueue *queue = MapNodePriorityQueue_new(map->mapNodeVector->size);

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


    while (!MapNodePriorityQueue_isEmpty(queue)) {
        processedNode = MapNodePriorityQueue_popMin(queue);


        if(processedNode != NULL && processedNode->distanceFromRoot != INT_MAX && processedNode == end) {
            isFound = true;
        }

        if(processedNode != NULL && processedNode->distanceFromRoot != INT_MAX) {

            for (size_t i = 0; i < RoadVector_getSize(processedNode->roadVector) && processedNode != end; i++) {
                Road *currentRoad = RoadVector_getRoadById(processedNode->roadVector, i);
                int roadTarget = currentRoad->destination_index;
                MapNode *currentNode = MapNodeVector_getMapNodeById(map->mapNodeVector, roadTarget);

                unsigned newDistance = processedNode->distanceFromRoot + currentRoad->length;

                if (currentNode->distanceFromRoot >= newDistance) {
                    int newAge = MapNode_getNewNodeOldestRoadAge(processedNode, currentRoad);
                    if(currentNode == end) {
                        if(newAge < end->oldestRoadAgeToMe) {
                            isExplicit = true;
                        }
                        else if(newAge == end->oldestRoadAgeToMe) {
                            isExplicit = false;
                        }
                    }
                    if(currentNode->distanceFromRoot > newDistance) {
                        parentIndex[currentNode->index] = processedNode->index;
                        updateNodeOldestRoadAge(processedNode, currentNode, currentRoad);
                        MapNodePriorityQueue_updateNode(queue, currentNode, newDistance);
                        if(currentNode == end) {
                            isExplicit = true;
                        }
                    }
                    else if(currentNode->distanceFromRoot == newDistance && newAge > currentNode->oldestRoadAgeToMe) {
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

static bool dijkstraWithForbiddenRouteWithException(Map *map, MapNode *start, MapNode *end, int parentIndex[], MapNodeList *route, MapNode *exception) {

    MapNodePriorityQueue *queue = MapNodePriorityQueue_new(map->mapNodeVector->size);

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
                unsigned newDistance = processedNode->distanceFromRoot + currentRoad->length;

                if ((currentNode == exception || !MapNodeList_isNodeIncludedInList(route, currentNode)) && currentNode->distanceFromRoot >= newDistance) {
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
                        if(currentNode == end) {
                            isExplicit = true;
                        }
                    }
                    if(currentNode->distanceFromRoot == newDistance && newAge > currentNode->oldestRoadAgeToMe) {
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

static MapNodeList *getNewRouteWithForbiddenRouteWithException(Map *map, unsigned routeId, MapNode *start, MapNode *end, MapNodeList *route, MapNode *exception) {
    int parentIndex[MapNodeVector_getSize(map->mapNodeVector)];

    if (!dijkstraWithForbiddenRouteWithException(map, start, end, parentIndex, route, exception)) {
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

    MapNodeList *routeAttachcedToStart = getNewRouteWithForbiddenRouteWithException(map, routeId, nodeToBeAdded, MapNodeList_getHeadNode(mainRoute), mainRoute, MapNodeList_getHeadNode(mainRoute));

    MapNodeList *routeAttachcedToEnd = getNewRouteWithForbiddenRouteWithException(map, routeId, MapNodeList_getTailNode(mainRoute), nodeToBeAdded, mainRoute, MapNodeList_getTailNode(mainRoute));


    int preference = MapNodeList_comparePreferenceOfRoutes(routeAttachcedToStart, routeAttachcedToEnd);
    int mainRouteIndexInVector = Vector_getElementVectorIndex(map->nationalRoadsVector, mainRoute);
    mainRoute = Vector_extractElementById(map->nationalRoadsVector, mainRouteIndexInVector);

    MapNodeList *newRoute = NULL;

    if(preference > 0) {
        MapNodeList_popTail(routeAttachcedToStart);
        newRoute = MapNodeList_mergeRoutes(routeAttachcedToStart, mainRoute, mainRoute->routeId);
        if(routeAttachcedToEnd != NULL) {
            MapNodeList_remove(routeAttachcedToEnd);
        }
    }
    else if(preference < 0) {
        MapNodeList_popTail(mainRoute);
        newRoute = MapNodeList_mergeRoutes(mainRoute, routeAttachcedToEnd, mainRoute->routeId);
        if(routeAttachcedToStart != NULL) {
            MapNodeList_remove(routeAttachcedToStart);
        }
    }
    else {
        if(routeAttachcedToStart != NULL) {
            MapNodeList_remove(routeAttachcedToStart);
        }
        if(routeAttachcedToEnd != NULL) {
            MapNodeList_remove(routeAttachcedToEnd);
        }
        Vector_add(map->nationalRoadsVector, mainRoute);
        return false;
    }

    Vector_add(map->nationalRoadsVector, newRoute);

    return true;
}

static Vector *getRouteWithIncludedConnectedNodes(Map *map, MapNode *node1, MapNode *node2) {
    Vector *routesToBeEditedVector = Vector_new(NULL);
    for(size_t i = 0; i < Vector_getSize(map->nationalRoadsVector); i++) {
        MapNodeList *route = (MapNodeList*) Vector_getElemById(map->nationalRoadsVector, i);
        bool rezult = MapNodeList_areConnectedNodesIncludedInRoad(route, node1, node2);
        if(rezult) {
            Vector_add(routesToBeEditedVector, route);
        }
    }
    if(Vector_isEmpty(routesToBeEditedVector)) {
        Vector_remove(routesToBeEditedVector);
        return NULL;
    }
    else {
        return routesToBeEditedVector;
    }
}

bool removeRoad(Map *map, const char *city1, const char *city2) {
    if(!map || !City_isNameValid(city1) || !City_isNameValid(city2)) {
        return false;
    }
    MapNode *node1 = Map_doesCityExist(map, city1);
    MapNode *node2 = Map_doesCityExist(map, city2);
    if(!node1 || !node2) {
        return false;
    }

    Road *roadToBeRemoved = MapNode_getRoadFromConnectedNodes(node1, node2);
    if(!roadToBeRemoved) {
        return false;
    }
    unsigned removeRoadLength = roadToBeRemoved->length;
    int removeRoadBuiltYear = roadToBeRemoved->buildYear;

    Vector *routesThatIncludeRoad = getRouteWithIncludedConnectedNodes(map, node1, node2);
    /* connect if failure */
    MapNode_disconnectNodes(node1, node2);
    if(!routesThatIncludeRoad) {
        return true;
    }

    Vector *newConnections = Vector_new(NULL);
    bool canBeConnected;
    bool connectionsStatus = true;

    /* gather information about roads that can be reconnected */
    for(size_t i = 0; i < Vector_getSize(routesThatIncludeRoad); i++) {
        MapNodeList *routeToBeEdited = (MapNodeList*) Vector_getElemById(routesThatIncludeRoad, i);
        MapNodeList_putMapNodesInOrder(routeToBeEdited, &node1, &node2);

        //connect is now connnection new connection betwwen nodes that connection has been removed
        MapNodeList *connect = getNewRouteWithForbiddenRouteWithException(map, routeToBeEdited->routeId, node1, node2, routeToBeEdited, node2);
        canBeConnected = (connect != NULL);
        if(!canBeConnected) {
            connectionsStatus = false;
        }
        if(canBeConnected) {
            Vector_add(newConnections, connect);
        }
    }
    /* if can not be connected undo changes */
    if(!connectionsStatus) {
        MapNode_connectMapNodes(node1, node2, removeRoadLength, removeRoadBuiltYear);
        Road_setAge(MapNode_getRoadFromConnectedNodes(node1, node2), removeRoadBuiltYear);
        Road_setAge(MapNode_getRoadFromConnectedNodes(node2, node1), removeRoadBuiltYear);
        Vector_remove(routesThatIncludeRoad);
        Vector_setFreeFunction(newConnections ,MapNodeList_remove);
        Vector_remove(newConnections);
        return false;
    }
    /* if reconnections are possible, make them  */
    /* removetmp all routes that need to be replaced */
    assert(Vector_getSize(routesThatIncludeRoad) == Vector_getSize(newConnections));
    for(size_t i = 0; i < Vector_getSize(newConnections); i++) {
        MapNodeList *routeToBeEdited = (MapNodeList*) Vector_getElemById(routesThatIncludeRoad, i);
        MapNodeList *routeToBeInjected = (MapNodeList*) Vector_getElemById(newConnections, i);
        MapNodeList_substituteConnWithRoute(routeToBeEdited, routeToBeInjected);
    }
    Vector_remove(newConnections);
    Vector_remove(routesThatIncludeRoad);

    return true;
}

char const* getRouteDescription(Map *map, unsigned routeId) {
    char *empty = malloc(sizeof(char));
    empty[0] = '\0';
    if (!map) {
        return empty;
    }
    MapNodeList *route = getRoutedById(map->nationalRoadsVector, routeId);
    if (!route) {
        return empty;
    }

    size_t size = getRouteDescriptionSize(route);

    char *string = malloc(size * sizeof(char));
    if(!string) {
        return empty;
    }

    putRouteDescription(route, string);
    free(empty);
    return string;
}

static bool validate_newCustomRouteVector(Map *map, Vector *routeParams) {
    bool result = true;
    char *city1Name, *city2Name;
    MapNode *city1, *city2;
    Road *conn;
    unsigned roadLen;
    int roadBuildYr;
    for(size_t i = 1; i < Vector_getSize(routeParams) - 3 && result; i += 3) {
        city1Name = (char*) String_getRaw(Vector_getElemById(routeParams, i));
        result = result && City_isNameValid(city1Name);
        city2Name = (char*) String_getRaw(Vector_getElemById(routeParams, i + 3));
        result = result && City_isNameValid(city2Name);
        roadLen = (unsigned) String_toInt(Vector_getElemById(routeParams, i + 1));
        roadBuildYr = (int) String_toInt(Vector_getElemById(routeParams, i + 2));
        result = result && (roadBuildYr != 0);

        if(result) {
            city1 = Map_doesCityExist(map, city1Name);
            city2 = Map_doesCityExist(map, city2Name);
            if (city1 != NULL && city2 != NULL) {
                conn = MapNode_getRoadFromConnectedNodes(city1, city2);
                if(conn != NULL) {
                    result = result && (Road_getLength(conn) == roadLen);
                    result = result && (Road_getAge(conn) <= roadBuildYr);
                }
            }
        }
    }
    return result;
}

bool newCustomRoute(Map *map, Vector *routeParams) {
    bool result = true;
    char *cityName1 = NULL;
    char *cityName2 = NULL;
    int routeId = String_toInt((String*) Vector_getElemById(routeParams, 0));
    /* routeId validation */
    if(!isRouteIdValid(routeId) || getRoutedById(map->nationalRoadsVector, routeId) != NULL) {
        return false;
    }
    /* validate vector */
    if(!validate_newCustomRouteVector(map, routeParams)) {
        return false;
    }
    Vector *cities = Vector_new(NULL);
    for(size_t i = 1; i < Vector_getSize(routeParams) - 3 && result; i += 3) {
        cityName1 = (char*) String_getRaw(Vector_getElemById(routeParams, i));
        cityName2 = (char*) String_getRaw(Vector_getElemById(routeParams, i + 3));
        unsigned roadLen = (unsigned) String_toInt((String*) Vector_getElemById(routeParams, i + 1));
        int roadBuildYr = (int) String_toInt((String*) Vector_getElemById(routeParams, i + 2));

        if(result && !addRoad(map, cityName1, cityName2, roadLen, roadBuildYr)) {
            MapNode *city1 = Map_doesCityExist(map, cityName1);
            MapNode *city2 = Map_doesCityExist(map, cityName2);
            Road *problematicRoad1to2 = MapNode_getRoadFromConnectedNodes(city1, city2);
            Road *problematicRoad2to1 = MapNode_getRoadFromConnectedNodes(city2, city1);
            Road_setAge(problematicRoad1to2, roadBuildYr);
            Road_setAge(problematicRoad2to1, roadBuildYr);
        }
        if(result) {
            result = result && Vector_add(cities, Map_doesCityExist(map, cityName1));
        }
    }
    result = result && Vector_add(cities, Map_doesCityExist(map, cityName2));
    if(!result) {
        Vector_remove(cities);
        return false;
    }
    MapNodeList *newRoute = MapNodeList_newCustomList(routeId, cities);
    if(newRoute == NULL) {
        result = false;
    }
    if(result && !Vector_add(map->nationalRoadsVector, newRoute)) {
        result = false;
    }
    Vector_remove(cities);
    return result;
}

bool removeRoute(Map *map, unsigned routeId) {
    if(!isRouteIdValid(routeId)) {
        return false;
    }
    MapNodeList *route = getRoutedById(map->nationalRoadsVector, routeId);
    if(route == NULL) {
        return false;
    }
    return Vector_removeElement(map->nationalRoadsVector, route);
}