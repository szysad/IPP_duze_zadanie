#ifndef __MAP_DEV_H__
#define __MAP_DEV_H__

#include "mapNodeVector.h"
#include "vector.h"
#include "mapNode_list.h"

typedef struct _map {
	MapNodeVector *mapNodeVector;
	Vector *nationalRoadsVector;
} Map;

Map* newMap(void);

void deleteMap(Map *map);

bool addRoad(Map *map, const char *city1, const char *city2, unsigned length, int builtYear);

bool repairRoad(Map *map, const char *city1, const char *city2, int repairYear);

bool newRoute(Map *map, unsigned routeId, const char *city1, const char *city2);


/* development */
void Map_print(Map *map);


#endif //__MAP_DEV_H__
