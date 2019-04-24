#include "map_dev.h"
#include <string.h>
#include <assert.h>

Map* newMap(void) {
	Map *map = malloc(sizeof(Map));
	map->mapNodeVector = MapNodeVector_new();

	return map;
}

void deleteMap(Map *map) {
	MapNodeVector_remove(map->mapNodeVector);
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

static MapNode *MapNode_getLessBranchedMapNode(MapNode *node1, MapNode *node2) {
	if(RoadVector_getSize(node1->roadVector) < RoadVector_getSize(node2->roadVector)) {
		return node1;
	}
	else {
		return node2;
	}
}

static MapNode *MapNode_getMoreBranchedMapNode(MapNode *node1, MapNode *node2) {
	if(RoadVector_getSize(node1->roadVector) < RoadVector_getSize(node2->roadVector)) {
		return node2;
	}
	else {
		return node1;
	}
}

/* slightly faster then MapNode_getRoadFromConnectedNodes(), doesnt specify road direction */
static bool MapNode_doesRoadExist(MapNode *node1, MapNode *node2) {
	MapNode *lessBranchedMapNode = MapNode_getLessBranchedMapNode(node1, node2);
	MapNode *moreBranchedMapNode = MapNode_getMoreBranchedMapNode(node1, node2);

	for(size_t i = 0; i < RoadVector_getSize(lessBranchedMapNode->roadVector); i++) {
		Road *checkedRoad = RoadVector_getRoadById(lessBranchedMapNode->roadVector, i);

		if(checkedRoad->destination_index == moreBranchedMapNode->index) {
			return true;
		}
	}
	return false;
}

static Road *MapNode_getRoadFromConnectedNodes(MapNode *start, MapNode *target) {
    for(size_t i = 0; i < RoadVector_getSize(start->roadVector); i++) {
        Road *checkedRoad = RoadVector_getRoadById(start->roadVector, i);

        if(checkedRoad->destination_index == target->index) {
            return checkedRoad;
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
    if(!City_isNameValid(city_name1) || !City_isNameValid(city_name2)) {
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


void Map_print(Map *map) {
    MapNodeVector_print(map->mapNodeVector);
}