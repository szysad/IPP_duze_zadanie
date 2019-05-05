#ifndef DROGI_CITY_H
#define DROGI_CITY_H

#include <zconf.h>
#include <stdbool.h>

typedef struct _city {
    size_t length;
    char *name;
} City;

City *City_new(const char *name);

void City_remove(City *city);

void City_print(City *city);

bool City_isNameValid(const char *name);

bool City_areNamesEqual(const char *name1, const char *name2);

#endif //DROGI_CITY_H
