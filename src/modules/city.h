/** @file
 * Interfejs struktury nazwy miasta.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#ifndef DROGI_CITY_H
#define DROGI_CITY_H

#include <zconf.h>
#include <stdbool.h>

/**
 * Struktura reprezentująca nazwę miasta.
 */
typedef struct _city {
    size_t length;
    char *name;
} City;

/**
 * @brief tworzy nową nazwię miasta.
 * @param[in] name : wskaźnik na tablicę charów.
 * @return wskaźnik na nową strukturę nazwy miasta lub NULL jeżeli nie udało zaalokować się pamięci.
 */
City *City_new(const char *name);

/**
 * @brief zwalnia pamięć struktury nazwy miasta.
 * @param[in,out] city : wskaźnik na struktuę nazwy miasta.
 */
void City_remove(City *city);

/**
 * @brief sprawdza poprawnosć nazyw miasta.
 * @param[in] name : wskaźnik na tablicę charów reprezentującą nazwe miasta.
 * @return @p true jeżeli tablica charów jest popraną nazwą miasta, false w przeciwnym przypadku.
 */
bool City_isNameValid(const char *name);

/**
 * @brief sprawdza czy podane napisy są takie same.
 * @param name1[in] : wskaźnik na napis1.
 * @param name2[in] : wskaźnik na napis2.
 * @return @p true jeżeli napis1 jest równy napisowi2, @p flase w przeciwnym przypadku
 */
bool City_areNamesEqual(const char *name1, const char *name2);

#endif //DROGI_CITY_H
