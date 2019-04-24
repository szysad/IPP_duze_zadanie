#include "map_dev.h"
#include <stdio.h>

int main() {

	Map *map = newMap();

	//printf("%d\n", addRoad(map, "gowno male", "twoja stara pijana", 10, 1));

	printf("%d\n", repairRoad(map, "gowno male", "twoja stara pijana", 1));


	Map_print(map);

	deleteMap(map);



}