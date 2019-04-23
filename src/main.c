#include "map_dev.h"
#include <stdio.h>

int main() {

	Map *map = newMap();
	
	printf("%d\n", addRoad(map, "gownom \0ale", "piękna baśń żeromskiego", 10, 1));
	printf("%d\n", addRoad(map, "el;o", "", 10, 0));
	printf("%d\n", addRoad(map, "e;lo", "elo1;234", 10, 2));
	printf("%d\n", addRoad(map, "gowno male3", "twoja stara pijana", 10, 3));
	printf("%d\n", addRoad(map, "gowno male34", "twoja stara pijana", 10, 3));

	Map_print(map);

	deleteMap(map);



}