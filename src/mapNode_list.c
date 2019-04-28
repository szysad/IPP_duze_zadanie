#include "mapNode_list.h"

static ListNode *ListNode_new(MapNode *node, ListNode *next) {
    ListNode *new = malloc(sizeof(ListNode));
    if(!new) {
        return NULL;
    }
    new->value = node;
    new->next = next;

    return new;
}

static void MapNodeList_removeNodes(MapNodeList *l) {
    ListNode *tmp = l->head;
    while(l->head != NULL) {
        tmp = l->head->next;
        free(l->head);
        l->head = tmp;
    }
}

MapNodeList *MapNodeList_new(size_t routeId) {
    MapNodeList *new = malloc(sizeof(MapNodeList));
    if(!new) {
        return NULL;
    }
    new->size = 0;
    new->routeId = routeId;
    new->head = NULL;
    new->tail = NULL;

    return new;
}

bool MapNodeList_append(MapNodeList *list, MapNode *mapNode) {
    ListNode *new = ListNode_new(mapNode, NULL);
    if(!new) {
        return false;
    }
    if(list->head == NULL) {
        list->head = new;
        list->tail = new;
    }
    else {
        list->tail->next = new;
        list->tail = new;
    }
    (list->size)++;
    return true;
}

void MapNodeList_remove(void *list) {
    MapNodeList_removeNodes((MapNodeList*)list);
    free(list);
}

bool isRouteIdValid(size_t routeId) {
    return (routeId < 999 && routeId > 0);
}

void MapNodeList_print(MapNodeList *list) {
    ListNode *elem = list->head;
    while (elem != NULL) {
        City_print(elem->value->city);
        elem = elem->next;
    }
}