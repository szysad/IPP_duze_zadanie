/** @file
 * Interfejs struktury węzła strukury mapy.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#ifndef __MAPNODE_H__
#define __MAPNODE_H__

#include "roadVector.h"
#include "city.h"

/**
 * Struktura reprezentująca miasto.
 */
typedef struct _mapNode {
	int index; ///< index miasta.
	City *city; ///< wskaźnik na struktuę nazwy miasta,
	RoadVector *roadVector; ///< wskaźnika na strukturę Vektora dróg wychodzących z miastsa.
    unsigned distanceFromRoot; ///< potrzebne dla algorytmów wyszukiwania optymalnej ścieżki
	int oldestRoadAgeToMe; ///< potrzebne dla algorytmów wyszukiwania optymalnej ścieżki
} MapNode;

/**
 * @brief tworzy nową strukturę miasta.
 * @param[in] city : wskaźnik na strukturę nazwy miasta.
 * @return wskaźnik na nowo utworzoną struktuę mapy, lub NULL jeżeli nie udało zaalokować się pamięci.
 */
MapNode *MapNode_new(City *city);

/**
 * @brief minimum.
 * @param[in] a : liczba1.
 * @param[in] b : liczba2.
 * @return liczba1 jeżeli liczba1 < liczba2, liczba2 w przeciwnym przypadku.
 */
long int min(int a, int b);

/**
 * @brief zwalnia pamięć miasta.
 * @param[in,out] mapNode : wskaźnik na struktuę mapy do zwolnienia pamięci.
 */
void MapNode_remove(MapNode *mapNode);

/**
 * @brief setter atrybuty setDistanceFromRoot.
 * @param[in,out] mapNode : wskaźnik na struktuę miasta do ustawienia atrybutu.
 * @param[in] distance : nowa wartość atrybutu.
 */
void MapNode_setDistanceFromRoot(MapNode *mapNode, unsigned distance);

/**
 * @brief setter atrybuty setOldestRoadAge.
 * @param[in,out] mapNode : wskaźnik na struktuę miasta do ustawienia atrybutu.
 * @param[in] distance : nowa wartość atrybutu.
 */
void MapNode_setOldestRoadAge(MapNode *mapNode, int age);

/**
 * @brief sprawdza czy dwa miasta są połączone drogą.
 * @param[in] node1 : miasto1.
 * @param[in] node2 : miasto2.
 * @return @p true jeżeli miasto1 i miasto2 są połączone odcinkiem drogi, @p false w przeciwnym przypadku.
 */
bool MapNode_doesRoadExist(MapNode *node1, MapNode *node2);

/**
 * @brief zwraca odcinek drogi łączącą podane miasta.
 * @param[in] start : miasto1.
 * @param[in] target : miasto2.
 * @return wskaźnika na strukturę odcinka drogi łączącej miasta1 i miasta2, NULL jeżeli oba miasta nie są połączone
 * odcinkiem drogi.
 */
Road *MapNode_getRoadFromConnectedNodes(MapNode *start, MapNode *target);

/**
 * @param[in] nodeFrom : wskaźnik na strukturę miasta.
 * @param[in] roadFromTo : wskaźnik na struktuę odcinka drogi.
 * @return minimun z atrybutu oldestRoadAgeToMe oraz wartości age podanego odcinka drogi.
 */
int MapNode_getNewNodeOldestRoadAge(MapNode *nodeFrom, Road *roadFromTo);

#endif //__MAPNODE_H__
