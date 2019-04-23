#ifndef __ROADVECTOR_H__
#define __ROADVECTOR_H__

#include "road.h"
#include <zconf.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _roadVector {
	size_t size;
	size_t capacity;
	Road **roadArray;
} RoadVector;


RoadVector *RoadVector_new();

bool RoadVector_add(RoadVector *vector, Road *road);

void RoadVector_remove(RoadVector *vector);

void RoadVector_removeRoadByIndex(RoadVector *vector, size_t index);

size_t RoadVector_getSize(RoadVector *vector);

Road *RoadVector_getRoadById(RoadVector *vector, size_t id);

void RoadVector_print(RoadVector *roadVector);


#endif //__ROADVECTOR_H__
