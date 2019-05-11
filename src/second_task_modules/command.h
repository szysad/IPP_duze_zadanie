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
	bool (*execute)(Map *map, Vector *args); ///< wskaźnik na funkcję wykonującą komendę na mapie.
} Command;

/**
 * @brief inicjalizuje nową komendę o podanych własnościach.
 * @param[in] name : wskaźnik na strukturę @see String przechowującą nazwę komendy.
 * @param[in] doesRawInputMatchTemplate : wskaźnik na funkcję sprawdzającą, czy tekst podany przez użytkownika pasuje do komendy.
 * Zwraca liczbę całkowią większą od 0, jeżeli składnia tekstu pasuje do komendy. 0 Jeżeli składna napisu nie pasuje do komendy.
 * Liczbę całkowitą mniejszą od 0, jeżeli nie udało zaalokować się pamięci.
 * Funkcja ma nie zwalniac pamięci napisu.
 * @param[in] validateInputsFunc : wskaźnik na funkcję sprawdzającą czy argumenty podane przez użytkownika są poprawne dla tej komendy.
 * funcja ma zwracać liczbę całkowitą większa od 0, jeżeli argumenty są poprawne.
 * 0 jeżeli argumenty są niepoprawne. Liczbę całkowitą mniejszą od 0, jeżeli nie udało zaalokowac się pamięci.
 * @param[in] sanitizeInputFunc : wskaźnik na funkcję sprowadzającą podany przez użytkownika tekst na Vektor poleceń komendy.
 * funkcja ma zwracać Vektor elementów typu @see String, które w takiej samej kolejności jak podanej przez użytkownika,
 * dają ciąg argumentów podanych przez użytkownika. Lub NULL jeżeli nie udało się zaalokować pamięci.
 * Funkcja ma nie zwalniac pamięci napisu.
 * @param[in] execute : wskaźnik na funckcję przeprowadzającą komendę na mapie.
 * Funkcja zwraca true jeżeli pomyślnie udało jej się komendę, w przeciwnym przypadku zwraca false i nie zmienia stanu mapy.
 * @return wskaźnik na nowo utworzoną strukturę komendy, lub NULL jeżeli nie udało zaalokować się pamięci.
 */
Command *Command_new(int (*doesRawInputMatchTemplate)(String *rawInput), int (*validateInputsFunc)(Vector *inputs), Vector *(*sanitizeInputFunc)(String *rawInput), bool (*execute)(Map *map, Vector *args));

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
bool Command_execute(Command *command, Map *map);

/**
 * @brief resetuje komende - przygotowuje do użycia z kolejnym tekstem podanym przez użytkownika.
 * @param[in,out] command : wskaźnik na strukturę resetowanej komendy.
 */
void Command_reset(Command *command);

#endif //DROGI_COMMAND_H
