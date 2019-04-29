#ifndef __MAPNODE_LIST_H__
#define __MAPNODE_LIST_H__

#include "mapNode.h"

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

bool isRouteIdValid(size_t routeId);

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

MapNode *MapNodeList_pop(MapNodeList *list);

void MapNodeList_setLength(MapNodeList *list, int length);

void MapNodeList_setOldestIncludedRoadAge(MapNodeList *list, int age);

#endif //__MAPNODE_LIST_H__
