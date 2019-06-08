/** @file
 * Interfejs funkcji komendy wykonującą operację extendRoute na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */

#ifndef DROGI_COMMAND_EXTENDROUTE_H
#define DROGI_COMMAND_EXTENDROUTE_H

#include "../second_task_modules/string.h"
#include "../map.h"

#include <stdbool.h>

/**
 * @brief @see Command_new;
 */
int _doesRawInputMatchExtendRoute(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _validateInputsExtendRoute(Vector *inputs);

/**
 * @brief @see Command_new;
 */
Vector *_sanitizeInputExtendRoute(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _executeExtendRoute(Map *map, Vector *args, String **output);


#endif //DROGI_COMMAND_EXTENDROUTE_H
