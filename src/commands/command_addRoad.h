/** @file
 * Interfejs zbioru funkcji komendy wykonującą operację addRoad na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 08.05.19
 */

#ifndef DROGI_COMMAND_ADDROAD_H
#define DROGI_COMMAND_ADDROAD_H

#include "../second_task_modules/string.h"
#include "../map.h"

#include <stdbool.h>

/**
 * @brief @see Command_new;
 */
int _doesRawInputMatchAddRoad(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _validateInputsAddRoad(Vector *inputs);

/**
 * @brief @see Command_new;
 */
Vector *_sanitizeInputAddRoad(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _executeAddRoad(Map *map, Vector *args, String **output);


#endif //DROGI_COMMAND_ADDROAD_H
