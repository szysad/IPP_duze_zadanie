#ifndef __MAP_DEV_H__
#define __MAP_DEV_H__

#include "modules/mapNodeVector.h"
#include "modules/vector.h"
#include "modules/mapNode_list.h"

typedef struct _map {
	MapNodeVector *mapNodeVector;
	Vector *nationalRoadsVector;
} Map;

Map* newMap(void);

void deleteMap(Map *map);

bool addRoad(Map *map, const char *city1, const char *city2, unsigned length, int builtYear);

bool repairRoad(Map *map, const char *city1, const char *city2, int repairYear);

bool newRoute(Map *map, unsigned routeId, const char *city1, const char *city2);

bool extendRoute(Map *map, unsigned routeId, const char *city);

bool removeRoad(Map *map, const char *city1, const char *city2);

/**
 * @brief tworzy nową drogę krajową o konkretnych odcinkach.
 * Jeżeli jakiś odcinek należący do nowo tworzonej drogi krajowej nie istnieje, to zostaje utworzony.
 * Jeżeli jakiś odcinek należący do nowo tworzonej drogi krajowej ma taką samą długoś jak przewiduje droga krajowa,
 * a jego rok budowy lub ostatniego remontu jest wcześniejszy niż przewiduje droga, to rok budowy lub ostatniego
 * remontu tego odcinka zostaje nadpisay przez wartość przewidywaną przez drogę krajową.
 * @param[in,out] map : wskaźnik na strukturę przechowującą mapę dróg.
 * @param[in] routeParams : wskaźnik na @see Vector wskaźników na @see String zawierających
 * informacje o nowo tworzonej drodze krajowej.
 * Vektor musi zawierać napisy identyczne do tych, jak w wyniku polecenia @see getRouteDescription().
 * @return Wartość @p true jeżeli udało stworzyć się nową drogę krajową i dodać ją do struktury mapy.
 * Wartość @p false jeżeli któryś z podanych parametrów jest niepoprawny, istnieje już droga krajowa o podanym
 * numerze, istnieje już odcinek drogi który miał być zawarty w drodze krajowej o długości innej niż
 * przewiduje nowo tworzona droga krajowa lub o roku budowy lub ostatniego remontu starszym niż przewiduje
 * nowo tworzona droga krajowa, nie udało zaalokować się pamięci.
 * W przypadku kiedy funkcja zwróciła wartość @p false z powodu innego niż to że istnieje już droga krajowa o
 * podanym numerze. Część miast i odcinków dróg zawartych w tworzonej drodze krajowej mogła zostać dodana do
 * struktury mapy, daty budowy lub ostatniego remontu części dróg należących do struktury mapy, które były
 * przewidziane w nowo tworzonej drodze krajowej mogły zostać zwiększone.
 */
bool newCustomRoute(Map *map, Vector *routeParams);

char const* getRouteDescription(Map *map, unsigned routeId);

/* development */
void Map_print(Map *map);


#endif //__MAP_DEV_H__
