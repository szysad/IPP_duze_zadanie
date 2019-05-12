/** @file
 * Interfejs zbioru funkcji komendy wykonującą operację getRouteDescription na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */

#ifndef DROGI_COMMAND_GETROUTEDESCRIPTION_H
#define DROGI_COMMAND_GETROUTEDESCRIPTION_H


#include "../second_task_modules/string.h"
#include "../map.h"

#include <stdbool.h>

/**
 * @brief @see Command_new;
 */
int _doesRawInputMatchGetRouteDesc(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _validateInputsGetRouteDesc(Vector *inputs);

/**
 * @brief @see Command_new;
 */
Vector *_sanitizeInputGetRouteDesc(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _executeGetRouteDesc(Map *map, Vector *args, String **output);


#endif //DROGI_COMMAND_GETROUTEDESCRIPTION_H
