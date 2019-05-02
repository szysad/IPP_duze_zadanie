#include "mapNode_list.h"
#include <string.h>

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
            assert(roadFromTo != NULL);
            newLength += roadFromTo->length;
            newOldestIncludedRoadAge = min(newOldestIncludedRoadAge, MapNode_getNewNodeOldestRoadAge(nodeFrom, roadFromTo));
        }
    }
    list->size = newSize;
    list->length = newLength;
    list->oldestIncludedRoadAge = newOldestIncludedRoadAge;
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
        (list->size)++;
        list->tail->next = new;
        list->tail = new;
        /* at this moment not necessary */
        //MapNodeList_updateParams(list);
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

bool MapNodeList_areConnectedNodesIncludedInRoad(MapNodeList *list, MapNode *node1, MapNode *node2) {
    /* assumption: start and end are connected */
    ListNode *elem = list->head;
    while (elem != NULL && (elem->value != node1 && elem->value != node2)) {
        elem = elem->next;
    }
    if(elem == NULL) {
        return false;
    }
    MapNode *firstInRoute = elem->value;
    elem = elem->next;
    MapNode *secondInRoute = elem->value;
    if(firstInRoute == node1) {
        return secondInRoute == node2;
    }
    else {
        return secondInRoute == node1;
    }
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

void MapNodeList_disconnectBetweenNodes(MapNodeList *list, MapNode *node1, MapNode *node2, MapNodeList **firstPart, MapNodeList **secondPart) {
    /* assumption node1, node2 are connected and both are included in list */
    assert(list->size >= 2);
    ListNode *elem = list->head;
    while (elem != NULL && (elem->value != node1 && elem->value != node2)) {
        elem = elem->next;
    }
    assert(elem != NULL && elem->next->value != NULL);
    MapNodeList *newRoute = MapNodeList_new(2137);
    if((elem->value == node1 && elem->next->value == node2) || (elem->value == node2 && elem->next->value == node1)) {
        newRoute->head = elem->next;
        newRoute->tail = list->tail;
        MapNodeList_updateParams(newRoute);
        list->tail = elem;
        list->tail->next = NULL;
        MapNodeList_updateParams(list);

        *firstPart = list;
        *secondPart = newRoute;
    }
    else {
        assert(false);
    }
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

    //MapNodeList_pop(list1);

    list1->tail->next = list2->head;

    MapNodeList *newList = MapNodeList_new(routeId);
    newList->head = list1->head;
    newList->tail = list2->tail;
    MapNodeList_updateParams(newList);

    free(list1);
    free(list2);

    return newList;
}

int countDigit(size_t n)
{
    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    return count;
}

size_t getRouteDescriptionSize(MapNodeList *list) {
    assert(!MapNodeList_isEmpty(list));

    ListNode *elem = list->head;
    MapNode *nodeFrom = list->head->value;
    MapNode *nodeTo = NULL;
    size_t size = 0;

    size += countDigit(list->routeId) + 1;// "routeId" + ";"
    while (elem != NULL) {
        nodeFrom = elem->value;
        size += nodeFrom->city->length; //"cityName" - "\0" + ";"
        elem = elem->next;
        if(elem) {
            nodeTo = elem->value;
            Road *roadFromTo = MapNode_getRoadFromConnectedNodes(nodeFrom, nodeTo);
            size += countDigit(roadFromTo->length) + 1; //"length" + ";"
            size += countDigit(Road_getAge(roadFromTo)) + 1; //"roadAge" + ";"
        }
    }
    return size + 1;// ... + "\0" - last";"
}

void putRouteDescription(MapNodeList *list, char string[]) {
    ListNode *elem = list->head;
    MapNode *nodeFrom = list->head->value;
    MapNode *nodeTo = NULL;
    char *tmp;

    sprintf(string, "%lu", list->routeId);
    strcat(string, ";");
    while (elem != NULL) {
        nodeFrom = elem->value;
        strcat(string, nodeFrom->city->name);
        if(elem && elem->next) {
            strcat(string, ";");
        }
        elem = elem->next;
        if(elem) {
            nodeTo = elem->value;
            Road *roadFromTo = MapNode_getRoadFromConnectedNodes(nodeFrom, nodeTo);
            tmp = malloc((countDigit(roadFromTo->length) + 1) * sizeof(char));
            sprintf(tmp, "%d", roadFromTo->length);
            strcat(string, tmp);
            strcat(string, ";");
            free(tmp);
            tmp = malloc((countDigit(Road_getAge(roadFromTo)) + 1) * sizeof(char));
            sprintf(tmp, "%d", Road_getAge(roadFromTo));
            strcat(string, tmp);
            strcat(string, ";");
            free(tmp);
        }
    }
    strcat(string, "\0");
}

void MapNodeList_print(MapNodeList *list) {
    ListNode *elem = list->head;
    while (elem != NULL) {
        //MapNode_print(elem->value);
        City_print(elem->value->city);
        elem = elem->next;
    }
    printf("oldest Included Road Age: %d\n", list->oldestIncludedRoadAge);
    printf("length: %d\n", list->length);
}