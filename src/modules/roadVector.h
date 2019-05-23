/** @file
 * Interfejs struktury Vektora dróg w strukturze mapy.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#ifndef __ROADVECTOR_H__
#define __ROADVECTOR_H__

#include "road.h"
#include <zconf.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * struktura vektora dróg.
 */
typedef struct _roadVector {
	size_t size; ///< ilośc elementów.
	size_t capacity; ///< rozmiar vektora.
	Road **roadArray; ///< tablica wskaźnikóœ na drogi.
} RoadVector;

/**
 * @brief tworzy nowy pusty wektor.
 * @return wskaźnik na utworzony wektor, NULL jeżeli nie udało zaalokować się pamięci.
 */
RoadVector *RoadVector_new();

/**
 * @brief dodaje miasto do vektora.
 * @param[in] vector : wskaźnik na vektor.
 * @param[in] road : wskaźnik na drogę.
 * @return true jeżeli udało dodać się drogę, false jeżeli nie udało zaalkować sie pamięci.
 */
bool RoadVector_add(RoadVector *vector, Road *road);

/**
 * zwalnia pamięć vectora
 * @param[in] vector : wskaźnik na vector.
 */
void RoadVector_remove(RoadVector *vector);

/**
 * @brief usuwa droge pod podanym indeksem.
 * @param vector : wsaźnik na vector.
 * @param index : indeks.
 */
void RoadVector_removeRoadByIndex(RoadVector *vector, size_t index);

/**
 * @param vector : wskaźnik na vector.
 * @param road : wskaźnik na drogę.
 * @return indeks drogi w vectorze lub -1 jeżeli się tam nie znajduje.
 */
int RoadVector_getRoadIndexInVector(RoadVector *vector, Road *road);

/**
 * @brief getter atrybutu size.
 * @param[in] vector : wskaźnik na vector.
 * @return wartość atrybutu size.
 */
size_t RoadVector_getSize(RoadVector *vector);

/**
 * @brief zwraca wskaźnik drogę znajdującym się pod podanym indeksem.
 * @param[in] vector : wskaźnik na vector.
 * @param[in] id : indeks.
 * @return wskaźnik na drogę znajdującym się pod podanym indeksem.
 */
Road *RoadVector_getRoadById(RoadVector *vector, size_t id);

#endif //__ROADVECTOR_H__
