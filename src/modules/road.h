#ifndef __ROAD_H__
#define __ROAD_H__

#include <zconf.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>


typedef struct _road {
    int buildYear;
	unsigned int length;
	int destination_index;
} Road;


Road *Road_new(unsigned int length, int age, int destination_index);

int Road_getAge(Road* road);

unsigned int Road_getLength(Road *road);

bool Road_areParamsValid(unsigned int length, int age);

void Road_setAge(Road *road, int age);

void Road_remove(Road *road);

#endif //__ROAD_H__
