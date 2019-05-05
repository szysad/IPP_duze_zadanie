#include "../map.h"

#include <stdlib.h>
#include <string.h>

#undef NDEBUG

#include <assert.h>

int main() {
    char const* str;

    Map* m = newMap();
    assert(m);

    assert(addRoad(m, "AlinÃ³w", "BÃ³r", 1, 2020));
    assert(addRoad(m, "BÃ³r", "CieliÅ„sk-NiekÅ‚aÅ„sk", 2, 2020));
    assert(addRoad(m, "BÃ³r", "DÄ…b Stary", 3, 2020));
    assert(addRoad(m, "CieliÅ„sk-NiekÅ‚aÅ„sk", "Emiliew", 4, 2020));
    assert(addRoad(m, "DÄ…b Stary", "Emiliew", 5, 2020));
    assert(addRoad(m, "Emiliew", "BÃ³r", 8, 2020));
    assert(addRoad(m, "Emiliew", "FraÅºnik Nowy", 3, 2020));
    assert(!repairRoad(m, "Emiliew", "CieliÅ„sk-NiekÅ‚aÅ„sk", 2019));
    assert(repairRoad(m, "Emiliew", "CieliÅ„sk-NiekÅ‚aÅ„sk", 2021));
    assert(!repairRoad(m, "Emiliew", "AlinÃ³w", 2020));
    assert(addRoad(m, "FraÅºnik Nowy", "Grzegrzewo", 4, 2020));
    assert(addRoad(m, "AlinÃ³w", "Grzegrzewo", 10, 2020));
    assert(addRoad(m, "Homilcin", "Grzegrzewo", 5, 2020));
    assert(addRoad(m, "FraÅºnik Nowy", "CieliÅ„sk-NiekÅ‚aÅ„sk", 2, 2020));
    assert(!addRoad(m, "FraÅºnik Nowy", "CieliÅ„sk-NiekÅ‚aÅ„sk", 2, 2020));
    assert(!addRoad(m, "CieliÅ„sk-NiekÅ‚aÅ„sk", "FraÅºnik Nowy", 2, 2020));
    assert(!repairRoad(m, "Emiliew", "BÃ³r", 2018));
    assert(repairRoad(m, "Emiliew", "CieliÅ„sk-NiekÅ‚aÅ„sk", 2021));
    assert(repairRoad(m, "Emiliew", "FraÅºnik Nowy", 2023));
    assert(addRoad(m, "Homilcin", "CieliÅ„sk-NiekÅ‚aÅ„sk", 3, 2020));
    assert(newRoute(m, 10, "AlinÃ³w", "Emiliew"));

    str = getRouteDescription(m, 10);
    assert(strcmp(str, "10;AlinÃ³w;1;2020;BÃ³r;2;2020;CieliÅ„sk-NiekÅ‚aÅ„sk;4;2021;Emiliew") == 0);
    free((void *)str);

    assert(extendRoute(m, 10, "Homilcin"));

    str = getRouteDescription(m, 10);
    assert(strcmp(str, "10;AlinÃ³w;1;2020;BÃ³r;2;2020;CieliÅ„sk-NiekÅ‚aÅ„sk;4;2021;Emiliew"
                       ";3;2023;FraÅºnik Nowy;4;2020;Grzegrzewo;5;2020;Homilcin") == 0);
    free((void *)str);

    deleteMap(m);

    return 0;
}