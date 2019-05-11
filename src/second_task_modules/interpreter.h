/** @file
 * Interfejs interpretera 2 części zadania.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#ifndef DROGI_INTERPRETER_H
#define DROGI_INTERPRETER_H


#include <zconf.h>
#include <stdbool.h>
#include "string.h"

/**
 * Struktura reprezentująca interpreter.
 */
typedef struct {
    size_t currentLine; ///< linia z której interpreter czyta dane.
} Interpreter;

/**
 * @brief inicjalizuje nowy interpreter.
 * @return wskaźnik na nowo zaalokowaną pustą strukturę interpretera, lub NULL jeżeli nie udało się zaalokować pamięci.
 */
Interpreter *Interpreter_new();

/**
 * @brief zwalnia pamieć struktury interpretera.
 * @param[in,out] interpreter : wskaźnik na strukturę interpretera która ma być zwolniona.
 * Mimo tego że argument tej funkcji jest typu void * to, zachowanie funkcji dla innego typu niż @see Interpreter jest
 * niezdefiniowane.
 */
void Interpreter_remove(void *interpreter);

/**
 * @brief wczytuje i zwraca wskaźnik na kolejną linie która nie jest komentarzem ze standardowego wejścia.
 * @return wskaźnik na struktuę typu @see String, reprezentującą kolejną wczytaną linię ze standardowego wejścia.
 * Zwraca NULL jeżeli nie udało zaalokować się pamięci.
 */
String *Interpreter_getLine(Interpreter *interpreter);

/**
 * @brief zwraca numer ostatnio czytanego wiersza z wejścia.
 * @param[in] interpreter : wskaźnik na strukturę interpretera.
 * @return numer ostatnio czytanego wiersza z wejścia.
 */
size_t Interpreter_getCurrentLine(Interpreter *interpreter);

#endif //DROGI_INTERPRETER_H
