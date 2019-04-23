#ifndef __MAP_DEV_H__
#define __MAP_DEV_H__

#include "mapNodeVector.h"

typedef struct _map {
	MapNodeVector *mapNodeVector;
} Map;

Map* newMap(void);

void deleteMap(Map *map);

bool addRoad(Map *map, const char *city1, const char *city2, unsigned length, int builtYear);

/* development */
void Map_print(Map *map);


#endif //__MAP_DEV_H__
