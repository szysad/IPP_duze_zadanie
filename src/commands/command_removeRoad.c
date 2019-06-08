/** @file
 * Implementacja funkcji komendy wykonującą operację removeRoad na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */

#include "command_removeRoad.h"
#include "command_common_functions.h"
#include <string.h>

static const unsigned int ARGS_EXPECTED = 3;
static const int MEM_END = -1;
static const char *KEYWORD = "removeRoad";

int _doesRawInputMatchRemoveRoad(String *rawInput) {
    Vector *args = preprocessInput(rawInput);
    bool result = (args != NULL);
    bool memFail = (args == NULL);
    result = result && (Vector_getSize(args) == ARGS_EXPECTED);
    result = result && (strcmp(KEYWORD, (char*) Vector_getElemById(args, 0)) == 0);
    result = result && City_isNameValid((char*) Vector_getElemById(args, 1));
    result = result && City_isNameValid((char*) Vector_getElemById(args, 2));
    recoverInput(rawInput);
    Vector_remove(args);
    if(memFail) {
        return MEM_END;
    }
    return result;
}

Vector *_sanitizeInputRemoveRoad(String *rawInput) {
    return _sanitizeInputDefault(rawInput);
}

int _validateInputsRemoveRoad(Vector *inputs) {
    return 1;
}

int _executeRemoveRoad(Map *map, Vector *args, String **output) {
    *output = NULL;
    const char* city1 = String_getRaw((String*) Vector_getElemById(args, 1));
    const char* city2 = String_getRaw((String*) Vector_getElemById(args, 2));
    return removeRoad(map, city1, city2);
}