#include <zconf.h>

/** @file
 * Implementacja zbioru funkcji komendy wykonującą operację getRouteDescription na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */


static const size_t ARGS_EXPECTED = 2;
static const int MEM_END = -1;
static const char *KEYWORD = "getRouteDescription";


#include "command_getRouteDescription.h"
#include "command_common_functions.h"
#include "string.h"

int _doesRawInputMatchGetRouteDesc(String *rawInput) {
    Vector *args = preprocessInput(rawInput);
    bool result = (args != NULL);
    bool memFail = (args == NULL);
    if(result && Vector_getSize(args) != ARGS_EXPECTED) {
        result = false;
    }
    if(result && strcmp(KEYWORD, (char*)Vector_getElemById(args, 0)) != 0) {
        result = false;
    }
    if(result && !isNumeric((char*)Vector_getElemById(args, 1))) {
        result = false;
    }
    recoverInput(rawInput);
    Vector_remove(args);

    if(memFail) {
        return MEM_END;
    }
    return result;
}

Vector *_sanitizeInputGetRouteDesc(String *rawInput) {
    return _sanitizeInputDefault(rawInput);
}

int _validateInputsGetRouteDesc(Vector *inputs) {
    String *routeId = (String*)Vector_getElemById(inputs, 1);

    String *intMaxStr = String_new("2147483647");
    String *intMinStr = String_new("-2147483648");

    bool rez = (intMaxStr != NULL && intMinStr != NULL);
    bool memFail = false;
    if(!rez) {
        memFail = true;
    }

    if(rez && String_compareInts(routeId, intMaxStr) > 0) {
        rez = false;
    }
    if(rez && String_compareInts(routeId, intMinStr) < 0) {
        rez = false;
    }

    String_remove(intMaxStr);
    String_remove(intMinStr);

    if(memFail) {
        return MEM_END;
    }
    return rez;
}

int _executeGetRouteDesc(Map *map, Vector *args, String **output) {
    char *desc = (char*) getRouteDescription(map, String_toInt(Vector_getElemById(args, 1)));
    *output = NULL;
    if(desc == NULL) {
        return MEM_END;
    }
    String *result = String_new(desc);
    if(result == NULL) {
        free(desc);
        return MEM_END;
    }
    if(String_isEmpty(result)) {
        free(desc);
        String_remove(result);
        return 0;
    }
    free(desc);
    *output = result;
    return 1;
}
