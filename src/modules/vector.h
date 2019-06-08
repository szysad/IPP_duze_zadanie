/** @file
 * Interfejs struktury generycznego Vektora.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>
#include <stdbool.h>

/**
 * struktur vectora.
 */
typedef struct {
    void **elementsArr; ///< talica elemtntów.
    size_t capacity; ///< rozmiar vectora.
    size_t size; ///< ilość elementów.
    void (*freeFunc)(void *); ///< funkcja zwalaniająca pamięć.
} Vector;

/**
 * @brief tworzy nowy pusty wektor.
 * @param freeFunc : wskaźnik na funkcję zwalniająca pamięć elementów.
 * @return wskaźnik na utworzony wektor, NULL jeżeli nie udało zaalokować się pamięci.
 */
Vector *Vector_new(void (*freeFunc)(void *));

/**
 * @brief dodaje element do tablicy.
 * @param vector : wskaźnik na vector.
 * @param element : wskaźnik na element.
 * @return true jeżeli udało się dodać, false jeżelni nie udało zaalokować się pamięci.
 */
bool Vector_add(Vector *vector, void *element);

void Vector_remove(Vector *v);

void Vector_setFreeFunction(Vector *vector, void (*freeFunction)(void *));

void *Vector_getElemById(Vector *vector, size_t id);

void *Vector_extractElementById(Vector *vector, size_t id);

int Vector_getElementVectorIndex(Vector *vector, void *elem);

bool Vector_isEmpty(Vector *vector);

size_t Vector_getSize(Vector *v);

/**
 * @brief usuwa element z wektora.
 * @param[in,out] v : wskaźnik na strukturę wektora.
 * @param[in] elem : wskaźnik na element która ma być z wektora usunięty.
 * @return @p true jeżeli udało usunąć się element z wektora. @p false jeżeli element do wektora nie należy.
 */
bool Vector_removeElement(Vector *v, void *elem);

#endif //__VECTOR_H__
