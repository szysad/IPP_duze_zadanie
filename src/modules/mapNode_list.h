#ifndef __MAPNODE_LIST_H__
#define __MAPNODE_LIST_H__

#include "mapNode.h"
#include "vector.h"
#include "../second_task_modules/string.h"
#include "../map.h"

typedef struct _listNode{
    MapNode *value;
    struct _listNode *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
    int size;
    int length;
    int oldestIncludedRoadAge;
    size_t routeId;
} MapNodeList;

MapNodeList *MapNodeList_new(size_t routeId);

bool MapNodeList_append(MapNodeList *list, MapNode *mapNode);

void MapNodeList_remove(void *list);

void MapNodeList_print(MapNodeList *list);

void MapNodeList_substituteConnWithRoute(MapNodeList *list, MapNodeList *sublist);

bool isRouteIdValid(size_t routeId);

void MapNodeList_putMapNodesInOrder(MapNodeList *list, MapNode **first, MapNode **second);

bool MapNodeList_isEmpty(MapNodeList *list);

bool MapNodeList_isNodeIncludedInList(MapNodeList* list, MapNode* node);

MapNode *MapNodeList_getHeadNode(MapNodeList *list);

MapNode *MapNodeList_getTailNode(MapNodeList *list);

bool MapNodeList_areConnectedNodesIncludedInRoad(MapNodeList *list, MapNode *start, MapNode *end);

void MapNodeList_disconnectBetweenNodes(MapNodeList *list, MapNode *node1, MapNode *node2, MapNodeList **firstPart, MapNodeList **secondPart);

/* if route1 more preferred then route2 returns 1
 * if route1 less preferred then route2 returns -1
 * if route1 and route2 have same preference returns 0 */
int MapNodeList_comparePreferenceOfRoutes(MapNodeList *route1, MapNodeList *route2);

/* attaches list1->tail into list2->head, updates params */
MapNodeList *MapNodeList_mergeRoutes(MapNodeList *list1, MapNodeList *list2, size_t routeId);

MapNode *MapNodeList_popTail(MapNodeList *list);

MapNode *MapNodeList_popHead(MapNodeList *list);

void MapNodeList_setLength(MapNodeList *list, int length);

void MapNodeList_setOldestIncludedRoadAge(MapNodeList *list, int age);

size_t getRouteDescriptionSize(MapNodeList *list);

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
MapNodeList *MapNodeList_newCustomList(int routeId, Vector *cities);

#endif //__MAPNODE_LIST_H__
