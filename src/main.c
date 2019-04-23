#include "map_dev.h"
#include <stdio.h>

int main() {

	Map *map = newMap();
	

	printf("%d\n", addRoad(map, "gowno male3", "twoja stara pijana", 10, 1));
	printf("%d\n", addRoad(map, "gowno male3", "twoja stara pijana", -1, 1));
	printf("%d\n", addRoad(map, "gowno male3", "", 1, 1));
	printf("%d\n", addRoad(map, "gowno m;ale3", "twoja staelora pija;na", 1, 1));
	printf("%d\n", addRoad(map, "gowasddsano male3", "twoja staelora pijana", 1, 1));
	printf("%d\n", addRoad(map, "gowno msale3", "tadswoja staelora pijana", 1, 1));
	printf("%d\n", addRoad(map, "gosdwno male3", "twoja staelora pijana", 1, 1));
	printf("%d\n", addRoad(map, "gowdsano male3", "twdoja staelora pijana", 1, 1));
	printf("%d\n", addRoad(map, "gowno male3", "twoja staelora pijana", 1, 1));
	printf("%d\n", addRoad(map, "gowno dmale3", "twojads staelora pijana", 1, 1));
	printf("%d\n", addRoad(map, "gowno male3", "twoja stddaelora pijana", 1, 1));

	Map_print(map);

	deleteMap(map);



}