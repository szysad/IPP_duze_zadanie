#include "city.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

static int FORIBIDDEN_CHAR_VAL_INF = 0;
static int FORIBIDDEN_CHAR_VAL_SUP = 31;

static bool isCityNameValid(const char *name) {
	int length = strlen(name) + 1;
	if(length == 1) {
		return false;
	}
	int i = 0;
	while(name[i] != '\0') {
		if((name[i] > FORIBIDDEN_CHAR_VAL_INF && name[i] < FORIBIDDEN_CHAR_VAL_SUP) || name[i] == ';') {
			return false;
		}
		i++;
	}
	return length - 1 == i;
}

City *City_new(const char *name) {
	if(!isCityNameValid(name)) {
		return NULL;
	}
	City *city = malloc(sizeof(City));
	if(!city) {
		return NULL;
	}
	city->length = strlen(name) + 1;
	city->name = malloc(city->length * sizeof(char));
	if(!city->name) {
		return NULL;
	}
	if(!strcpy(city->name, name)) {
		return NULL;
	}

	return city;

}

void City_remove(City *city) {
	assert(city != NULL && city->name != NULL);
	free(city->name);
	free(city);
}

void City_print(City *city) {
    printf("\tcity: %s\n", city->name);
    printf("\tname len: %ld\n", city->length);
}