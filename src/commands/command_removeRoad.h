/** @file
 * Interfejs funkcji komendy wykonującą operację removeRoad na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */

#ifndef DROGI_COMMAND_REMOVEROAD_H
#define DROGI_COMMAND_REMOVEROAD_H


#include "../second_task_modules/string.h"
#include "../map.h"

#include <stdbool.h>

/**
 * @brief @see Command_new;
 */
int _doesRawInputMatchRemoveRoad(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _validateInputsRemoveRoad(Vector *inputs);

/**
 * @brief @see Command_new;
 */
Vector *_sanitizeInputRemoveRoad(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _executeRemoveRoad(Map *map, Vector *args, String **output);


#endif //DROGI_COMMAND_REMOVEROAD_H
