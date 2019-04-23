#ifndef __ROAD_H__
#define __ROAD_H__

#include <zconf.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>


typedef struct _road {
	int buildYear;
	int lastRepairYear;
	int length;
	int destination_index;
} Road;


Road *Road_new(int age, int length, int destination_index);

bool Road_areParamsValid(int length, int age);

void Road_setAge(Road *road, int age);

void Road_remove(Road *road);

void Road_print(Road *road);

#endif //__ROAD_H__
