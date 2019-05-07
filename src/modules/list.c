/** @file
 * Implementacja interfejsu listy
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 05.05.19
 */

#include "list.h"
#include <stdlib.h>

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
    new->freeFunction = freeFunction;
    return new;
}

void List_remove(List *list) {
    _LNode *tmp = list->head;
    while(list->head != NULL) {
        tmp = list->head->next;
        if(list->freeFunction != NULL) {
            list->freeFunction(tmp->value);
        }
        free(list->head);
        list->head = tmp;
    }
}

bool List_append(List *list, void *value) {
    _LNode *new = newNode(NULL, value);
    if(new == NULL) {
        return false;
    }
    if(list->head == NULL) {
        list->head = new;
        list->tail = new;
    }
    else {
        list->tail->next = new;
    }
    (list->size)++;
    return true;
}

bool List_isEmpty(List *list) {
    return list->head == NULL;
}

void *List_popHead(List *list) {
    _LNode *poped = list->head;
    void *popVal = poped->value;
    list->head = poped->next;
    free(poped);
    (list->size)--;
    return popVal;
}
