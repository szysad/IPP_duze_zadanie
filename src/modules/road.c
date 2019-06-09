/** @file
 * Implementacja struktury odcinka drogi w strukturze mapy.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */


#include "road.h"
#include <stdlib.h>

Road *Road_new(unsigned int length, int age, int destination_index) {
	Road *road = malloc(sizeof(Road));
	if(!road) {
		return NULL;
	}
	road->buildYear = age;
	road->length = length;
	road->destination_index = destination_index;

	return road;
}

unsigned int Road_getLength(Road *road) {
	return road->length;
}

void Road_setAge(Road *road, int lastRepairYear) {
	road->buildYear = lastRepairYear;
}

void Road_remove(Road *road) {
	free(road);
}

bool Road_areParamsValid(unsigned int length, int age) {
	return (age != 0 && length > 0);
}

int Road_getAge(Road* road) {
	return road->buildYear;
}