/** @file
 * Interfejs struktury Vektora węzłów struktury mapy krajowej.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#ifndef __MAPNODEVECTOR_H__
#define __MAPNODEVECTOR_H__

#include "mapNode.h"

/**
 * struktura vektora miast.
 */
typedef struct _mapNodeVector {
	size_t size; ///< ilosć elementów w vektorze.
	size_t capacity; //< rozmiar wektora.
	MapNode **mapNodeArray; ///< tablica wskaźników na miasta.
} MapNodeVector;

/**
 * @brief tworzy nowy pusty wektor.
 * @return wskaźnik na utworzony wektor, NULL jeżeli nie udało zaalokować się pamięci.
 */
MapNodeVector *MapNodeVector_new();

/**
 * @brief dodaje miasto do vektora.
 * @param[in] vector : wskaźnik na vektor.
 * @param[in] mapNode : wskaźnik na miasto.
 * @param[out] added_index : indeks pod jakim został dodany element w vectorze.
 * @return true jeżeli udało dodać się miasto, false jeżeli nie udało zaalkować sie pamięci.
 */
bool MapNodeVector_add(MapNodeVector *vector, MapNode *mapNode, int *added_index);

/**
 * zwalnia pamięć vectora
 * @param[in] vector : wskaźnik na vector.
 */
void MapNodeVector_remove(MapNodeVector *vector);

/**
 * @brief getter atrybutu size.
 * @param[in] vector : wskaźnik na vector.
 * @return wartość atrybutu size.
 */
size_t MapNodeVector_getSize(MapNodeVector *vector);

/**
 * @brief zwraca wskaźnik miasto znajdującym się pod podanym indeksem.
 * @param[in] vector : wskaźnik na vector.
 * @param[in] id : indeks.
 * @return wskaźnik na miasto znajdującym się pod podanym indeksem.
 */
MapNode *MapNodeVector_getMapNodeById(MapNodeVector *vector, size_t id);

#endif //__MAPNODEVECTOR_H__
