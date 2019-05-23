/** @file
 * Interfejs zbioru funkcji komendy wykonującą operację newRoute na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 08.05.19
 */
#ifndef DROGI_COMMAND_NEWROUTE_H
#define DROGI_COMMAND_NEWROUTE_H

#include "../second_task_modules/string.h"
#include "../map.h"

/**
 * @brief @see Command_new;
 */
int _doesRawInputMatchNewRoute(String *rawInput);

/**
 * @brief @see Command_new;
 */
Vector *_sanitizeInputNewRoute(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _validateInputsNewRoute(Vector *inputs);

/**
 * @brief @see Command_new;
 */
int _executeNewRoute(Map *map, Vector *args, String **output);

#endif //DROGI_COMMAND_NEWROUTE_H
