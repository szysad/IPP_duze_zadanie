#include "road.h"
#include <stdlib.h>

Road *Road_new(int age, int length, int destination_index) {
	Road *road = malloc(sizeof(Road));
	if(!road) {
		return NULL;
	}
	road->buildYear = age;
	road->lastRepairYear = 0;
	road->length = length;
	road->destination_index = destination_index;

	return road;
}

void Road_setAge(Road *road, int lastRepairYear) {
    road->lastRepairYear = lastRepairYear;
}

void Road_remove(Road *road) {
	free(road);
}

bool Road_areParamsValid(int length, int age) {
    return (age != 0 && length > 0);
}

/* development */
void Road_print(Road *road) {
    printf("\t\troad buildYear: %d\n", road->buildYear);
    if(road->lastRepairYear == 0) {
        printf("\t\troad not repaired yet\n");
    }
    else {
        printf("\t\troad last repair year: %d\n", road->lastRepairYear);
    }
    printf("\t\troad len: %d\n", road->length);
    printf("\t\troad dest_index: %d\n", road->destination_index);
}