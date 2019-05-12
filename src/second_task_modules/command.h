/** @file
 * Interfejs Komendy.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */


#ifndef DROGI_COMMAND_H
#define DROGI_COMMAND_H

#include "string.h"
#include "../map.h"

/**
 *  Struktura przechowująca informacje i procedury komendy.
 */
typedef struct {
	bool isreadyToExecute; ///< zawiera informację czy tekst komendy przeszedł wstępna validację.
	Vector *args; ///< wskaźnik na vektor, przechowującą w kolejności od pierwszego do ostatniego parametru podanego przez użytkownika.
	int (*doesRawInputMatchTemplate)(String *rawInput); ///< wskaźnik na funkcję sprawdzającą, czy tekst podany przez użytkownika pasuje do komendy.
	int (*validateInputsFunc)(Vector *inputs); ///< wskaźnik na funkcję sprawdzającą czy argumenty podane przez użytkownika są poprawne dla tej komendy.
	Vector *(*sanitizeInputFunc)(String * rawInput); ///< wskaźnik na funkcję sprowadzającą podany przez użytkownika tekst na Vektor poleceń komendy.
	int (*execute)(Map *map, Vector *args, String **output); ///< wskaźnik na funkcję wykonującą komendę na mapie.
} Command;


/**
 * //TODO rozbij na poszczególne dokumentacje 4 funkcji.
 * @brief inicjalizuje nową komendę o podanych własnościach.
 * @param[in] name : wskaźnik na strukturę @see String przechowującą nazwę komendy.
 * @param[in] doesRawInputMatchTemplate : wskaźnik na funkcję sprawdzającą, czy tekst podany przez użytkownika
 * pasuje do komendy. Dokładna specyfukacja tej funkcji jest opisana tutaj @see doesRawInputMatchTemplate().
 * @param[in] sanitizeInputFunc : wskaźnik na funkcję przekształcającą tekst podany przez użytkownika, którego składnia
 * pasuje dla tej komendy, na @see Vector poszczególnych argumentów zawartych w tekście użytkownika. Szczegółowa
 * specyfikacja tej funkcji jest opisana tutaj @see sanitizeInputFunc().
 * @param[in] validateInputsFunc : wskaźnik na funkcję sprawdzającą czy argumenty podane przez użytkownika są poprawne
 * dla tej komendy. Dokładna specyfikacji tej funkcji jest opisana tutaj @see validateInputsFunc().
 * @param[in] execute : wskaźnik na funckcję przeprowadzającą komendę na mapie i zwracającej napis do wypisania na
 * wyjście. Dokładna specyfukacja znajduje się tutaj @see execute().
 * @return wskaźnik na nowo utworzoną strukturę komendy, lub NULL jeżeli nie udało zaalokować się pamięci.
 */
Command *Command_new(
                    int (*doesRawInputMatchTemplate)(String *rawInput),
                    Vector *(*sanitizeInputFunc)(String *rawInput),
                    int (*validateInputsFunc)(Vector *inputs),
                    int (*execute)(Map *map, Vector *args, String **output)
                    );

/**
 * @brief sprawdza czy składnia wiersza z wejścia pasuje dla komendy implementującą tą funkcję.
 * @param[in] rawInput : wskaźnik na strukturę napisu reprezentującą linię z wejścia.
 * @return liczbę całkowitą większą od 0, jeżeli składnia napisu pasuje dla komendy.
 * 0 jeżeli składnia napisu nie pasuje dla komendy.
 * Liczba całkowita mniejsza od 0, jeżeli nie udało zaalokowac się pamięci.
 */
int (*doesRawInputMatchTemplate)(String *rawInput);

/**
 * @brief tworzy @see Vector argumentów potrzebnych do wykonania operacji na mapie.
 * @param[in] rawInput : wskaźnik na strukturę @see String zawierającą wiersz dostarczony przez @see Interpreter_getLine()
 * @return wskaźnik na @see Vector wskaźników na @see String zawierające odzielne argumenty podane w wierszu
 * dostarczonym przez @see Interpreter_getLine(). Lub NULL jeżeli nie udało zaalokować się pamięci.
 */
Vector *(*sanitizeInputFunc)(String *rawInput);

/**
 * @brief dokonuje wstępnej validacji logicznej dostarczonych argumentów.
 * @param[in] rawInput : wskźnik na @see Vector wskaźników na struktury @see String zawierające argumenty potrzebne do
 * wykonania komendy na mapie.
 * @return liczba całkowita większa od 0, jeżeli argumenty przeszły validacje. 0 Jeżeli nie przeszły validacji.
 * Liczba całkowita mniejsza od 0, jeżeli nie udało zaalokować się pamięci.
 */
int (*validateInputsFunc)(Vector *inputs);

/**
 * @brief wykonuje operację komendy na mapie, zwraca napis do wypisania na wyjście.
 * @param[in,out] map : wskaźnik na strukturę mapy, na której komenda ma zostać wykonana.
 * @param[in] args : wskaźnik na @see Vector uzyskany od funkcji @see sanitizeInputFunc(), który przeszedł validację
 * funkcji @see validateInputsFunc().
 * @param[in,out] output : wskaźnik na wskaźnik @see String zawierający napis do wypisania na wyjście, przyjmuje
 * wartość NULL jeżeli nic nie ma do wypisania.
 * @return liczba całkowita większa od 0, jeżeli udało się przeprowadzić operację na mapie.
 * 0 Jeżeli nie udało się przeprowadzić operacji na mapie.
 * Liczba całkowita mniejsza od 0, jeżeli nie odało zaalokowac się pamięci.
 */
int (*execute)(Map *map, Vector *args, String **output);

/**
 * @brief zwalnia pamięć struktury komendy.
 * @param[in,out] command : wskaźnik na strukturę komendy której pamięć zostanie zwolniona.
 */
void Command_remove(void *command);

/**
 * @brief sprawdza czy składnia tekstu użytkownika jest poprawna dla tej komendy.
 * @param[in] command : komenda.
 * @param[in] rawInput : wskaźnik na tablicę znaków zawierający surowy tekst podany przez użytkownika.
 * @return Liczbę całkowitą większą od 0, jeżeli składnia napisu pasuje do komendy. 0 Jeżeli nie pasuje.
 * Liczbę całkowią mniejszą od 0, jeżeli nie udało zaalokować się pamięci.
 */
int Command_doesRawInputMatchTemplate(Command *command, String *rawInput);

/**
 * @brief sprawdza czy podany tekst ma poprawną składnię i wykonuje część logicznej validacji. Pozwala na wykonanie komendy.
 * @param[in, out] command : komenda której dotyczy validacja, jeżeli funkcja zwróci true komenda może wykonać operację @see Command_execute.
 * @return Liczbę całkowita większa od 0 jeżeli tekst ma poprawną składnię.
 * 0 Jeżeli tekst ma niepoprawną składnie. Liczbę całkowitą mniejszą od 0 jeżeli nie udało zaalokować się pamięci,
 */
int Command_validateInput(Command *command, String *rawInput);


/**
 * @brief wykonuje komendę na podanej mapie, jeżeli komenda przeszła validację.
 * Jeżeli ostatnie wywołanie funkcji @see Command_validateInput dla tej komendy zwróciło false, to wywołanie tej funkcji
 * zakończy się błędem.
 * @param[in] command : wskaźnik na strukturę komendy.
 * @param[in,out] map : wskaźnik na strukturę mapy.
 * @return true jeżeli komenda została wykonana na podanej strukturze mapy, false jeżeli komenda zakończyła się
 * niepowodzeniem, w takim przypadku struktura mapy nie ulega zmianie.
 */
int Command_execute(Command *command, Map *map);

/**
 * @brief resetuje komende - przygotowuje do użycia z kolejnym tekstem podanym przez użytkownika.
 * @param[in,out] command : wskaźnik na strukturę resetowanej komendy.
 */
void Command_reset(Command *command);

#endif //DROGI_COMMAND_H
