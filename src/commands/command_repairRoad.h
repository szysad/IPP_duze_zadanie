/** @file
 * Interfejs zbioru funkcji komendy wykonującą operację repairRoad na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */

#ifndef DROGI_COMMAND_REPAIRROAD_H
#define DROGI_COMMAND_REPAIRROAD_H


#include "../second_task_modules/string.h"
#include "../map.h"

#include <stdbool.h>

/**
 * @brief @see Command_new;
 */
int _doesRawInputMatchRepairRoad(String *rawInput);

/**
 * @brief @see Command_new;
 */
Vector *_sanitizeInputRepairRoad(String *rawInput);

/**
 * @brief @see Command_new;
 */
int _validateInputsRepairRoad(Vector *inputs);

/**
 * @brief @see Command_new;
 */
int _executeRepairRoad(Map *map, Vector *args, String **output);


#endif //DROGI_COMMAND_REPAIRROAD_H
