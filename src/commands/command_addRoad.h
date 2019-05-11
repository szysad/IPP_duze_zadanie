/** @file
 * Interfejs komendy wykonującą operację addRoad na mapie.
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
int doesRawInputMatchTemplateAddRoad(String *rawInput);

/**
 * @brief @see Command_new;
 */
int validateInputsFuncAddRoad(Vector *inputs);

/**
 * @brief @see Command_new;
 */
Vector *sanitizeInputFuncAddRoad(String *rawInput);

/**
 * @brief @see Command_new;
 */
bool executeAddRoad(Map *map, Vector *args);


#endif //DROGI_COMMAND_ADDROAD_H
