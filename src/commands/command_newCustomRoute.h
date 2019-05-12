/** @file
 * Interfejs zbioru funkcji komendy wykonującą operację newCustomRoute na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 08.05.19
 */

#ifndef DROGI_COMMAND_NEWCUSTOMROUTE_H
#define DROGI_COMMAND_NEWCUSTOMROUTE_H


#include "../second_task_modules/string.h"
#include "../map.h"

#include <stdbool.h>

/**
 * @brief @see Command_new;
 */
int _doesRawInputMatchNewCustomRoute(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _validateInputsNewCustomRoute(Vector *inputs);

/**
 * @brief @see Command_new;
 */
Vector *_sanitizeInputNewCustomRoute(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _executeNewCustomRoute(Map *map, Vector *args, String **output);


#endif //DROGI_COMMAND_NEWCUSTOMROUTE_H
