/** @file
 * Interfejs zbioru funckji implementowanych przez część komęnd.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */

#ifndef DROGI_COMMAND_COMMON_FUNCTIONS_H
#define DROGI_COMMAND_COMMON_FUNCTIONS_H


#include "../modules/vector.h"
#include "../second_task_modules/string.h"

/**
 * @brief rozdziela napis na zbiór wskaźników na tablice napisów w stylu C. Podział następuję w miejscu znaku ";".
 * Zwraca vektor zawierający te poroździelane napisy.
 * Przykład: napis w stylu "a;b;c;...;x;y;z" przetworzy na vektor napisów ("a","b","c",...,"x","y","z").
 * @param[in,out] inputStr : wskaźnik na strukturę napisu reprezentujący główny napis do porozdzielania pozyskaną przez
 * @see Interpreter zawarty w pliku "second_task_modules/interpreter.h".
 * Od momentu użycia funkcji @see preprocessInput do momentu użuca funkcji @see recoverInput, na wskaźniku struktury
 * reprezentującej napis, inne funkcje tego napisu nie będą działać poprawnie.
 * @return wskaźnik na vektor podzielonych napisów w stylu C. Lub NULL jeżeli nie udało się zaalokować pamięci.
 */
Vector *preprocessInput(String *inputStr);

/**
 * @brief naprawia strukturę napisu po użyciu funkcji @see preprocessInput.
 * @param[in,out] inputStr : napis do naprawienia.
 */
void recoverInput(String *inputStr);

/**
 * @brief sprawdza czy napis w stylu C, reprezentuje liczbę całkowitą.
 * W rozumieniu tej funkcji poprawna liczba całkowita to każdy ciąg cyfr mogący zaczynać się znakiem "-". Poza ciągami
 * z wyłączeniem znaku "-", długości większej niż 1 zaczynjące się znakiem "0".
 * @paramp[in] input : napis w stylu C.
 * @return true jeżeli napis spełnia wyżej podaną definicję liczby całkowiter, false w przeciwnym wypadku.
 */
bool isNumeric(const char *input);

/**
 * @brief realizuje funkcjonalność komendy sanitizeInput. W standardowy sposób.
 * @param[in] rawInput : napis zawierający wiersz z wejścia standardowego, pozyskane przez @see Interpreter_getLine.
 * @return @see Vector wskaźników na struktury napisów reprezentujących poszczególne argumenty zawarte w wierszu wejścia.
 */
Vector *_sanitizeInputDefault(String *rawInput);


#endif //DROGI_COMMAND_COMMON_FUNCTIONS_H
