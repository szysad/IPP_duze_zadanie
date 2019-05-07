#include "map.h"

#include <stdlib.h>

#include <assert.h>
#include "modules/list.h"
#include "modules/string.h"
#include "string.h"

static int dk2str(unsigned dk, char *str) {
    int i = 3;
    do {
        --i;
        str[i] = dk % 10 + '0';
        dk /= 10;
    } while (dk);
    return i;
}

#define DK(_map, _dk, _descr)                           \
  do {                                                  \
    char const *_str = getRouteDescription(_map, _dk);  \
    assert(_str);                                       \
    assert(strcmp(_str, _descr) == 0);                  \
    free((void *)_str);                                 \
  } while (0)

#define CITY_COUNT 1000

int main() {
    Map* m = newMap();
    assert(m);

    assert(addRoad(m, "a", "b", 1, 2));

    deleteMap(m);
    return 0;
}