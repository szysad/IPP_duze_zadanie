#include "road.h"
#include <stdlib.h>

Road *Road_new(int age, int length, int destination_index) {
	if(age == 0 || length <= 0) {
		return NULL;
	}
	Road *road = malloc(sizeof(Road));
	if(!road) {
		return NULL;
	}
	road->age = age;
	road->length = length;
	road->destination_index = destination_index;

	return road;
}

void Road_remove(Road *road) {
	free(road);
}

/* development */
void Road_print(Road *road) {
    printf("\t\troad age: %d\n", road->age);
    printf("\t\troad len: %d\n", road->length);
    printf("\t\troad dest_index: %d\n", road->destination_index);
}