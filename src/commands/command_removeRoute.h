/** @file
 * Interfejs zbioru funkcji komendy wykonującą operację removeRoute na mapie.

 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */

#ifndef DROGI_COMMAND_REMOVEROUTE_H
#define DROGI_COMMAND_REMOVEROUTE_H

#include "../second_task_modules/string.h"
#include "../modules/vector.h"
#include "../map.h"

/**
 * @brief @see Command_new;
 */
int _doesRawInputMatchRemoveRoute(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _validateInputsRemoveRoute(Vector *inputs);

/**
 * @brief @see Command_new;
 */
Vector *_sanitizeInputRemoveRoute(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _executeRemoveRoute(Map *map, Vector *args, String **output);


#endif //DROGI_COMMAND_REMOVEROUTE_H
