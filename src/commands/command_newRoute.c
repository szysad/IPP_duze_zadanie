/** @file
 * Implementacja zbioru funkcji komendy wykonującą operację newRoute na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 08.05.19
 */

#include "command_newRoute.h"
#include "command_common_functions.h"
#include <stdbool.h>
#include <string.h>

static const unsigned int ARGS_EXPECTED = 4;
static const int MEM_END = -1;
static const char *KEYWORD = "newRoute";

int _doesRawInputMatchNewRoute(String *rawInput) {
    Vector *args = preprocessInput(rawInput);
    bool result = (args != NULL);
    bool memFail = (args == NULL);

    result = result && (Vector_getSize(args) == ARGS_EXPECTED);
    result = result && (strcmp(KEYWORD, (char*) Vector_getElemById(args, 0)) == 0);
    result = result && isNumeric((char*) Vector_getElemById(args, 1));
    result = result && City_isNameValid((char*) Vector_getElemById(args, 2));
    result = result && City_isNameValid((char*) Vector_getElemById(args, 3));
    recoverInput(rawInput);
    Vector_remove(args);

    if(memFail) {
        return MEM_END;
    }
    return result;
}

Vector *_sanitizeInputNewRoute(String *rawInput) {
    return _sanitizeInputDefault(rawInput);
}

int _validateInputsNewRoute(Vector *inputs) {
    String *routeId = (String*)Vector_getElemById(inputs, 1);
    String *uintMaxStr = String_putInt(UINT_MAX);
    String *uintMinStr = String_putInt(0);

    bool rez = (uintMaxStr != NULL && uintMinStr != NULL);
    bool memFail = false;
    if(!rez) {
        memFail = true;
    }

    rez = rez && (String_compareInts(routeId, uintMaxStr) <= 0);
    rez = rez && (String_compareInts(routeId, uintMinStr) >= 0);

    String_remove(uintMinStr);
    String_remove(uintMaxStr);
    if(memFail) {
        return MEM_END;
    }
    return rez;
}

int _executeNewRoute(Map *map, Vector *args, String **output) {
    *output = NULL;
    unsigned routeId = (unsigned) String_toInt((String*) Vector_getElemById(args, 1));
    const char* city1 = String_getRaw((String*) Vector_getElemById(args, 2));
    const char* city2 = String_getRaw((String*) Vector_getElemById(args, 3));

    return newRoute(map, routeId, city1, city2);

}