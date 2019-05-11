/** @file
 * Implementacja interfejsu listy
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 05.05.19
 */

#include "list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/**
 * @brief tworzy nowy węzeł listy.
 * @param[in] next : wskaźnik na następnik nowego węzła.
 * @param[in,out] value : wskażnik na zawartość węzła.
 * @return wskaźnik na nowo zaalokowany węzeł, lub NULL jeżeli nie udało się zaalokowac pamięci.
 */
static _LNode *newNode(_LNode *next, void *value) {
    _LNode *new = malloc(sizeof(_LNode));
    if(new == NULL) {
        return NULL;
    }
    new->value = value;
    new->next = next;
    return new;
}

List *List_new(void (*freeFunction)(void *)) {
    List *new = malloc(sizeof(List));
    if(new == NULL) {
        return NULL;
    }
    new->size = 0;
    new->tail = NULL;
    new->head = NULL;
    new->lastGet = NULL;
    new->lastGetIndex = 0;
    new->freeFunction = freeFunction;
    return new;
}

/**
 * @brief zwalnia pamięć podanego węzła i jego następników.
 * @param[in,out] head : węzeł do zwolnienia jego pamięci i jego następników.
 * @param freeFunc : funkcja zwalniająca pamieć zawartości węzłów listy.
 */
static void List_removeNodes(_LNode *head, void (*freeFunc)(void *)) {
    _LNode *tmp = head;
    while (head != NULL) {
        tmp = head->next;
        if(freeFunc != NULL) {
            freeFunc(head->value);
        }
        free(head);
        head = tmp;
    }
}

void List_reset(List *list) {
    List_removeNodes(list->head, list->freeFunction);
    list->head = NULL;
    list->tail = NULL;
    list->lastGet = NULL;
    list->size = 0;
}

void List_remove(void *listV) {
    List *list = (List*) listV;
    List_removeNodes(list->head, list->freeFunction);
    free(list);
}

bool List_append(List *list, void *value) {
    _LNode *new = newNode(NULL, value);
    if(new == NULL) {
        return false;
    }
    if(list->head == NULL) {
        list->head = new;
    }
    else {
        list->tail->next = new;
    }
    list->tail = new;
    (list->size)++;
    return true;
}

bool List_isEmpty(List *list) {
    return list->head == NULL;
}

void *List_popHead(List *list) {
    _LNode *poped = list->head;
    if(list->lastGet == poped) {
        list->lastGet = NULL;
    }
    void *popVal = poped->value;
    list->head = poped->next;
    free(poped);
    (list->size)--;
    return popVal;
}

void *List_get(List *list, size_t index) {
    assert(index < list->size);
    if(list->lastGet == NULL || index < list->lastGetIndex) {
        list->lastGet = list->head;
        list->lastGetIndex = 0;
    }
    while (list->lastGetIndex < index) {
        list->lastGet = list->lastGet->next;
        (list->lastGetIndex)++;
    }
    return list->lastGet->value;
}


void List_print(List *list, void (*printFunction)(void *value)) {
    _LNode *tmp = list->head;
    while (tmp != NULL) {
        printFunction(tmp->value);
        tmp = tmp->next;
    }
}