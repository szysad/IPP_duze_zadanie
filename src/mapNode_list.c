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
    new->oldestIncludedRoadAge = INT_MAX;
    new->length = 0;
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
        return true;
    }
    else {
        Road *road = MapNode_getRoadFromConnectedNodes(list->tail->value, new->value);
        assert(road != NULL);
        (list->length) += road->length;
        (list->size)++;
        list->oldestIncludedRoadAge = min(list->oldestIncludedRoadAge, MapNode_getNewNodeOldestRoadAge(list->tail->value, road));
        list->tail->next = new;
        list->tail = new;
        return true;
    }
}

void MapNodeList_remove(void *list) {
    MapNodeList_removeNodes((MapNodeList*)list);
    free(list);
}

bool isRouteIdValid(size_t routeId) {
    return (routeId < 999 && routeId > 0);
}

void MapNodeList_setLength(MapNodeList *list, int length) {
    list->length = length;
}

void MapNodeList_setOldestIncludedRoadAge(MapNodeList *list, int age) {
    list->oldestIncludedRoadAge = age;
}

bool MapNodeList_isNodeIncludedInList(MapNodeList* list, MapNode* node) {
    ListNode *elem = list->head;
    while (elem != NULL && elem->value != node) {
        elem = elem->next;
    }
    return (elem != NULL && elem->value == node);
}

MapNode *MapNodeList_getHeadNode(MapNodeList *list) {
    if(!list->head) {
        return NULL;
    }
    return list->head->value;
}

MapNode *MapNodeList_getTailNode(MapNodeList *list) {
    if(!list->tail) {
        return NULL;
    }
    return list->tail->value;
}

bool MapNodeList_isEmpty(MapNodeList *list) {
    return (list->head == NULL);
}

void MapNodeList_updateParams(MapNodeList *list) {
    assert(!MapNodeList_isEmpty(list));
    int newOldestIncludedRoadAge = INT_MAX;
    int newLength = 0;
    int newSize = 0;

    ListNode *elem = list->head;
    MapNode *nodeFrom = elem->value;
    MapNode *nodeTo = NULL;
    while (elem != NULL) {
        newSize++;
        nodeFrom = elem->value;
        elem = elem->next;
        if(elem) {
            nodeTo = elem->value;
            Road *roadFromTo = MapNode_getRoadFromConnectedNodes(nodeFrom, nodeTo);
            newLength += roadFromTo->length;
            newOldestIncludedRoadAge = min(newOldestIncludedRoadAge, MapNode_getNewNodeOldestRoadAge(nodeFrom, roadFromTo));
        }
    }
    list->size = newSize;
    list->length = newLength;
    list->oldestIncludedRoadAge = newOldestIncludedRoadAge;
}

MapNode *MapNodeList_pop(MapNodeList *list) {
    assert(!MapNodeList_isEmpty(list));
    ListNode *elem = list->head;
    ListNode *elemBefore = elem;
    while(elem != list->tail) {
        elemBefore = elem;
        elem = elem->next;
    }
    MapNode *poppedNode = list->tail->value;
    list->tail = elemBefore;
    list->tail->next = NULL;
    free(elem);
    MapNodeList_updateParams(list);

    return poppedNode;
}

int MapNodeList_comparePreferenceOfRoutes(MapNodeList *route1, MapNodeList *route2) {
    if(route1->length < route2->length) {
        return 1;
    }
    else if(route2->length < route1->length) {
        return -1;
    }
    else {
        if(route2->oldestIncludedRoadAge < route1->oldestIncludedRoadAge) {
            return 1;
        }
        if(route1->oldestIncludedRoadAge < route2->oldestIncludedRoadAge) {
            return -1;
        }
        else {
            return 0;
        }
    }
}

MapNodeList *MapNodeList_mergeRoutes(MapNodeList *list1, MapNodeList *list2, size_t routeId) {
    assert(!MapNodeList_isEmpty(list1));

    MapNodeList_pop(list1);
    list1->tail->next = list2->head;

    MapNodeList *newList = MapNodeList_new(routeId);
    newList->head = list1->head;
    newList->tail = list2->tail;
    MapNodeList_updateParams(newList);

    free(list1);
    free(list2);

    return newList;
}

void MapNodeList_print(MapNodeList *list) {
    ListNode *elem = list->head;
    while (elem != NULL) {
        City_print(elem->value->city);
        elem = elem->next;
    }
    printf("oldest Included Road Age: %d\n", list->oldestIncludedRoadAge);
    printf("length: %d\n", list->length);
}