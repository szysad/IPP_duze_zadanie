#include "road.h"
#include <stdlib.h>

Road *Road_new(int length, int age, int destination_index) {
	Road *road = malloc(sizeof(Road));
	if(!road) {
		return NULL;
	}
	road->buildYear = age;
	road->length = length;
	road->destination_index = destination_index;

	return road;
}

int Road_getLength(Road *road) {
    return road->length;
}

void Road_setAge(Road *road, int lastRepairYear) {
    road->buildYear = lastRepairYear;
}

void Road_remove(Road *road) {
	free(road);
}

bool Road_areParamsValid(int length, int age) {
    return (age != 0 && length > 0);
}

int Road_getAge(Road* road) {
    return road->buildYear;
}

/* development */
void Road_print(Road *road) {
    printf("\t\troad buildYear: %d\n", road->buildYear);
    if(road->buildYear == 0) {
        printf("\t\troad not repaired yet\n");
    }
    else {
        printf("\t\troad last repair year: %d\n", road->buildYear);
    }
    printf("\t\troad len: %d\n", road->length);
    printf("\t\troad dest_index: %d\n", road->destination_index);
}