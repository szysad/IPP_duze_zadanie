/** @file
 * Interfejs struktury odcinka drogi w strukturze mapy.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#ifndef __ROAD_H__
#define __ROAD_H__

#include <zconf.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/**
 * struktura drogi.
 */
typedef struct _road {
    int buildYear; ///< rok budowy lub ostatniego remontu.
	unsigned int length; ///< długość drogi.
	int destination_index; ///< cel.
} Road;

/**
 * @param length : długość drogi.
 * @param age : wiek.
 * @param destination_index : indeks celu.
 * @return wskaźnik na utworzoną droge, lub NULL jeżlei nie udało zaalokować się pamieci.
 */
Road *Road_new(unsigned int length, int age, int destination_index);

/**
 * getter atrybutu buildYear.
 * @param[in] road : wskaźnik na drogę.
 * @return wartość atrybutu buildYear.
 */
int Road_getAge(Road* road);

/**
 * getter atrybutu length.
 * @param[in] road : wskaźnik na drogę.
 * @return wartość atrybutu length.
 */
unsigned int Road_getLength(Road *road);

/**
 * @param length długośc
 * @param age wiek.
 * @return true jeżeli podane wartości są poprawne, false w pp.
 */
bool Road_areParamsValid(unsigned int length, int age);

/**
 * gesettertter atrybutu buildYear.
 * @param[in] road : wskaźnik na drogę.
 */
void Road_setAge(Road *road, int age);

/**
 * @brief zwalania pamięć.
 * @param road : wskażnik na drogę.
 */
void Road_remove(Road *road);

#endif //__ROAD_H__
