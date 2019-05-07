/** @file
 * Interfejs listy
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 05.05.19
 */

#ifndef DROGI_LIST_H
#define DROGI_LIST_H

#include <stdbool.h>
#include <zconf.h>

/**
 * Struktura przechowująca węzły listy.
 */
typedef struct _node {
    void *value; ///< wskaźnik na zawartość węzła.
    struct _node *next; ///< wskaźnik na następny węzeł listy.
} _LNode;

/**
 * Struktura przechowująca listę.
 */
typedef struct {
    size_t size; ///< liczba elementów listy.
    _LNode *head; ///< wskaźnik na pierwszy węzeł listy.
    _LNode *tail; ///< wkaźnik na ostatni węzeł listy.
    void (*freeFunction)(void *); ///< funkcja zwalnijąca pamięć zawartości węzłów listy.
} List;

/**
 * @brief inicjalizuje nową listę.
 * @param[in] freeFunction : wskaźnik na funkcję zwalniajacą pamięć zawartości węzłów listy.
 * @return wskaźnik na nową pustą listę, lub NULL jeżeli nie udało się zaalokowac pamięci.
 */
List *List_new(void (*freeFunction)(void *));

/**
 * @brief zwalnia pamięć listy.
 * Podczas wykonywania tej funkcji wszytkie elementy zawarte w węzłach listy, są poddawne funkcji podanej przy inicjalizacji listy.
 * @param[in,out] list : lista do zwolnienia.
 */
void List_remove(List *list);

/**
 * @brief dodaje element na koniec listy.
 * @param[in,out] list : lista która zostanie przedłużona.
 * @param[in, out] value : element który zostaje dodany do listy.
 * @return true jeżeli udało się zaalokować pamięć, false jeżeli nie udało zaalokować się pamięci.
 */
bool List_append(List *list, void *value);

/**
 * @brief usuwa pierwszy węzeł nie pustej listy i zwraca wskaźnik na jego zawartość.
 * Ta funkcja na pustej liście zpowoduje błąd.
 * @param[in,out] list : lista od której element zostanie odłączony.
 * @return wskaźnik na zawartość usuwanego węzła listy.
 */
void *List_popHead(List *list);

/**
 * @brief sprawdza czy lista jest pusta.
 * @param[in] list : sprawdzana lista.
 * @return true jeżeli lista jest pusta, false jeżeli nie jest pusta.
 */
bool List_isEmpty(List *list);

#endif //DROGI_LIST_H
