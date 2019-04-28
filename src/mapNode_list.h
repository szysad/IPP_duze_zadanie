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
    size_t routeId;
} MapNodeList;

MapNodeList *MapNodeList_new(size_t routeId);

bool MapNodeList_append(MapNodeList *list, MapNode *mapNode);

void MapNodeList_remove(void *list);

void MapNodeList_print(MapNodeList *list);

bool isRouteIdValid(size_t routeId);

#endif //__MAPNODE_LIST_H__
