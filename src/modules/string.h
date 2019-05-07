/** @file
 * Interfejs stringu (napisu)
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 05.05.19
 */

#ifndef DROGI_STRING_H
#define DROGI_STRING_H

#include <zconf.h>

/**
 * Struktura reprezentująca napis.
 * Napis to tablica znaków, która zna swój rozmiar.
 */
typedef struct {
    char *body; ///< tablica znaków.
    size_t length; ///< długosć napisu.
} String;

/**
 * @brief tworzy nowy napis, o zawarości podanej przez tablicę znaków.
 * @param[in] charArr tablica znaków zakończona znakiem "NULL terminated".
 * @return wskaźnik na nowy napis, lub NULL jeżeli nie udało się zaalokować pamięci.
 */
String *String_new(char *charArr);

/**
 * @brief zwalnia pamięć napisu.
 * Mimo tego, że typ parametru jest typu (void*) to funkcja dla typu innego niż (String*) spowoduje błąd.
 * @param String[in,out] : wskaźnik na strukturę @see String, której pamięć ma ulec zwolnieniu.
 */
void String_remove(void *string);

#endif //DROGI_STRING_H
