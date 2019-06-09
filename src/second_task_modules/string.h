/** @file
 * Interfejs stringu (napisu)
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 05.05.19
 */

#ifndef DROGI_STRING_H
#define DROGI_STRING_H

#include <zconf.h>
#include <stdbool.h>

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

/**
 * @brief zwraca wskaźnik na tablicę znaków reprezentującą zawierającą napis.
 * @param[in] string : wskaźnik na napis który ma zwrócić wskaźnik na tablicę znaków.
 * @return wskaźnik na tablicę znaków reprezentującą napis.
 */
char *String_getRaw(String *string);

/**
 * @brief zwraca długość napisu bez znaku '\0' na końcu.
 * @param[in] string : napis.
 * @return długosć napisu.
 */
size_t String_getLength(String *string);

/**
 * @brief wypisuje napis na standardowe wyjście.
 * @param[in] string : wskaźnik na napis do wypisania.
 */
void String_print(void *string);

/**
 * @brief sprawdza czy napisy są identyczne.
 * @param[in] string1 : wskaźnik na pierwszy napis.
 * @param[in] string2 : wskaźnik na drugi napis.
 * @return true jeżeli napisy są identyczne, false w przeciwnym przypadku.
 */
bool String_equals(String *string1, String *string2);

/**
 * @brief zwraca long int'a zapisanego jako podany napis.
 * @param[in] string : napis w stylu C, który zawiera jedynie znaki '0'-'9' ale może zaczynać się znakiem '-'
 * reprezentującym liczbę ujemną.
 * Niedozwolony jest zapis liczby wielocyfrowej zaczynającej się zerem jak i liczby reprezentującej zero
 * zaczynającej się znakiem minus.
 * Dla napisów zawierających inne znaki zachowanie nie jest zdefiniowane.
 * @return int zapisany jako podany napis.
 */
long int String_toInt(String *string);

/**
 * @brief tworzy tekstową reprezentację liczby całkowitej z zakresu long int.
 * @param[in] : liczba typu long int.
 * @return wskaźnik na nowo utworzoną strukturę @see String reprezentującą liczbę typu long int.
 * NULL jeżeli nie udało zaalokowac się pamięci,
 */
String *String_putInt(long int input);

/**
 * @brief porównuje dwie liczby zapisane jako napisy.
 * @param[in] string1 : liczba 1.
 * @param[in] string2 : liczba 2.
 * napis reprezentujacy liste to ciąg znaków, który zawiera jedynie znaki '0'-'9' ale może zaczynać się znakiem '-'
 * reprezentującym liczbę ujemną.
 * Niedozwolony jest zapis liczby wielocyfrowej zaczynającej się zerem jak i liczby reprezentującej zero
 * zaczynającej się znakiem '-'.
 * @return 1 jeżeli string1 reprezentuje liczbę większą niż string2,
 * -1 jeżeli string1 reprezentuje liczbę mniejszą niż string2,
 * 0 jeżeli string1 i string2 reprezentują taką samą liczbę.
 */
int String_compareInts(String *string1, String *string2);

#endif //DROGI_STRING_H
