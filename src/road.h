#ifndef __ROAD_H__
#define __ROAD_H__

#include <zconf.h>
#include <stdio.h>


typedef struct _road {
	int age;
	int length;
	int destination_index;
} Road;


Road *Road_new(int age, int length, int destination_index);

void Road_remove(Road *road);

void Road_print(Road *road);

#endif //__ROAD_H__
