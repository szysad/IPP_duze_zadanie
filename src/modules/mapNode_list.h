/** @file
 * Interfejs struktury drogi krajowej.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#ifndef __MAPNODE_LIST_H__
#define __MAPNODE_LIST_H__

#include "mapNode.h"
#include "vector.h"
#include "../second_task_modules/string.h"
#include "../map.h"

/**
 * Struktura reprezentująca węzeł listy drogi krajowej.
 */
typedef struct _listNode{
	MapNode *value; ///< wskaźnik na strukturę miasta.
	struct _listNode *next; ///< wskaźnik na następnik w liście drogi krajowej.
} ListNode;

/**
 * Struktura reprezentująca drogę krajową
 */
typedef struct {
	ListNode *head; ///< wskaźnik na pierwszye element w liście drogi krajowej.
	ListNode *tail; ///< wskaźnik na ostatni element w liście drogi krajowej.
	int size; ///< ilosc miast w drodze krajowej.
	int length; ///< łączna długość drogi krajowej.
	int oldestIncludedRoadAge; ///< wiek najstarszego odcinka w drodze krajowej.
	unsigned routeId; ///< numer drogi krajowej.
} MapNodeList;

/**
 * @brief tworzy nową drogę krajową
 * @param[in] routeId : numer drogi krajowej.
 * @return wskaźnik na nową, pustą drogę krajową, lub NULL jeżeli nie udało zaalokować się pomięci.
 */
MapNodeList *MapNodeList_new(unsigned routeId);

/**
 * @brief dodaje miasto na koniec drogi krajowej i aktualizuje jej atrybuty.
 * @param[in,out] list : wskaźnik na struktuę drogi krajowej.
 * @param[in] mapNode : wskaźnik na strukturę miasta.
 * @return true jeżeli udało dodać się miasto do drogi krajowej, false jeżeli nie udało zaalokować się pamięci.
 */
bool MapNodeList_append(MapNodeList *list, MapNode *mapNode);

/**
 * @brief zwalania pamięć struktury drogi krajowej.
 * @param[in,out] list : wskażnik na strukturę drogi krajowej do usunięcia.
 */
void MapNodeList_remove(void *list);

/**
 * @brief podmienia odcinek drogi krajowej inną drogą krajową.
 * @param[in,out] list : wskaźnik na drogę krajową której odcinek ma zostać podmieniony.
 * @param[in,out] sublist : wskaźnik na strukturę drogi krajowej która ma zostać wstawiona na miejsce odcinka
 * drogi krajowej.
 */
void MapNodeList_substituteConnWithRoute(MapNodeList *list, MapNodeList *sublist);

/**
 * @param[in] routeId : numer drogi krajowej.
 * @return @p true jeżeli podany numer drogi krajowej jest dozwolony, @p false w przeciwnym przypadku.
 */
bool isRouteIdValid(unsigned routeId);

/**
 * @brief ustawia podane wskaźniki na wskaźniki struktue miast tak żeby pierwszy podany występował pierwszy w
 * podanej drogi krajowej.
 * @param[in] list : wskaźnik na drogę krajową.
 * @param[in,out] first : wskaźnik na wskaźnik na strukturę miasta.
 * @param[in,out] second : wskaźnik na wskaźnik na strukturę miasta.
 */
void MapNodeList_putMapNodesInOrder(MapNodeList *list, MapNode **first, MapNode **second);

/**
 * @param[in] list : wskażni na strukturę drogi krajowej,
 * @return @p true jeżeli droga krajowa jest pusta, @p false w przeciwnym przypadku.
 */
bool MapNodeList_isEmpty(MapNodeList *list);

/**
 * @param[in] list : wskaźnik na struktuę drogi krajowej.
 * @param[in] node : wskaźnik na strukturę miasta.
 * @return @p true jeżeli podane miasto należy do podanje drogi krajowej, @p false w przeciwnym przypadku.
 */
bool MapNodeList_isNodeIncludedInList(MapNodeList* list, MapNode* node);

/**
 * @param[in] list : wskaźnik na struktuę drogi krajowej.
 * @return wskaźnik na atrubut head podanej drogi krajowej.
 */
MapNode *MapNodeList_getHeadNode(MapNodeList *list);

/**
 * @param[in] list : wskaźnik na struktuę drogi krajowej.
 * @return wskaźnik na atrubut tail podanej drogi krajowej.
 */
MapNode *MapNodeList_getTailNode(MapNodeList *list);

/**
 * @brief sprawdza czy podana para różnych miast i łączący ich odcinek drogi krajowej jest zawart w podanej
 * drodze krajowa.
 * @param[in] list : wskaźnik na struktuę drogi krajowej.
 * @param[in] start : wskaźnik na strukturę miasta.
 * @param[in] end : wskaźnik na strukturę miasta.
 * @return true jeżeli podana para różnych miast jest zawarta w drodze krajowej. False w przeciwnym przypadku,
 */
bool MapNodeList_areConnectedNodesIncludedInRoad(MapNodeList *list, MapNode *start, MapNode *end);

/* if route1 more preferred then route2 returns 1
 * if route1 less preferred then route2 returns -1
 * if route1 and route2 have same preference returns 0 */
/**
 * @brief porównuje preferencje dróg krajowych.
 * @param[in] route1 : wskaźnik na strukturę miasta1.
 * @param[in] route2 : wskaźnik na strukturę miasta2.
 * @return -1 jeżeli miasto1 ma wyższą preferencję niż miasto2, 0 jeżeli masto1 i miasto2 mają takie same preferencje
 * 1 w innym wypadku.
 */
int MapNodeList_comparePreferenceOfRoutes(MapNodeList *route1, MapNodeList *route2);
/**
 * @brief tworzy nową drogę krajową z połącznia dwóch dróg krajowych.
 * @param[in] list1 : wskaźnik na strukturę drogi krajowej która będzie rozpoczynała nową drogę krajową.
 * @param[in] list2 : wskaźnik na strukturę drogi krajowej która będzie kończyła nową drogę krajową.
 * @param[in] routeId : numer nowej drogi krajowej.
 * @return wskaźnik na nową drogę krajową, lub NULL jeżeli nie udało zaalokować się pamięci.
 */
MapNodeList *MapNodeList_mergeRoutes(MapNodeList *list1, MapNodeList *list2, unsigned routeId);

/**
 * @brief zwraca wskaźnik na ostatni element drogi krajowej po czym usuwa go z drogi krajowej.
 * @param[in,out] list : wskaźnik na strukturę niepustej drogi krajowej.
 * @return wskaźnik na strukuturę usunietego miasta z drogi krajowej.
 */
MapNode *MapNodeList_popTail(MapNodeList *list);

/**
 * @brief zwraca wskaźnik na pierwszy element drogi krajowej po czym usuwa go z drogi krajowej.
 * @param[in,out] list : wskaźnik na strukturę niepustej drogi krajowej.
 * @return wskaźnik na strukuturę usunietego miasta z drogi krajowej.
 */
MapNode *MapNodeList_popHead(MapNodeList *list);

/**
 * @brief setter atrybutu length drogi krajowej.
 * @param[in,out] list : wskaźnik na strukturę drogi krajowej.
 * @param[in] length : nowa długość.
 */
void MapNodeList_setLength(MapNodeList *list, unsigned length);

/**
 * @brief setter atrybutu oldestIncludedRoadAge drogi krajowej.
 * @param[in,out] list : wskaźnik na strukturę drogi krajowej.
 * @param[in] length : nowa wartość atrybutu oldestIncludedRoadAge.
 */
void MapNodeList_setOldestIncludedRoadAge(MapNodeList *list, int age);

/**
 * @param[in] list : wskaźnik na strukturę drogi krajowej.
 * @return liczba znaków która będzie zajęta przez funkcję getRouteDescription().
 */
size_t getRouteDescriptionSize(MapNodeList *list);

/**
 * @brief generuje napis dla funkcji getRouteDescription;
 * @param[in] list : wskaźnik na strukturę drogi krajowej.
 * @param string : tablica charów z zaalokowaną odpowiednia ilościa pamięci.
 */
void putRouteDescription(MapNodeList *list, char string[]);

/**
 * @brief tworzy nową drogę krajową o określonych miastach.
 * Nowa droga krajowa będzie utworzona tak aby przechodziła przez miasta w kolejności takiej, jak miasta zostały
 * dodane do Vektora. Aby funkcja działa poprawanie każdy odcinek drogi zawart w nowo tworzonej drodze krajowej
 * musi być połączony drogą.
 * @param[in] routeId : numer nowej drogi krajowej.
 * @param[in] cities : @see Vector wskaźników na miasta przez które ma przechodzić nowa droga.
 * @return wskaźnik na nowo utworzoną drogę krajową. NULL jeżeli nie da się utworzyć takiej drogi krajowej, lub
 * nie udało się zaalokować pamięci.
 */
MapNodeList *MapNodeList_newCustomList(unsigned routeId, Vector *cities);

#endif //__MAPNODE_LIST_H__
