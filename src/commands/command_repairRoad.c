/** @file
 * Implementacja zbioru funkcji komendy wykonującą operację repairRoad na mapie.

 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */

#include <zconf.h>

static const size_t ARGS_EXPECTED = 4;
static const int MEM_END = -1;
static const char *KEYWORD = "repairRoad";

#include "string.h"
#include "command_repairRoad.h"
#include "command_common_functions.h"

int _doesRawInputMatchRepairRoad(String *rawInput) {

    Vector *args = preprocessInput(rawInput);
    bool result = (args != NULL);
    bool memFail = (args == NULL);
    if(result && Vector_getSize(args) != ARGS_EXPECTED) {
        result = false;
    }
    if(result && strcmp(KEYWORD, (char*)Vector_getElemById(args, 0)) != 0) {
        result = false;
    }
    if(result && !City_isNameValid((char*)Vector_getElemById(args, 1))) {
        result = false;
    }
    if(result && !City_isNameValid((char*)Vector_getElemById(args, 2))) {
        result = false;
    }
    if(result && !isNumeric((char*)Vector_getElemById(args, 3))) {
        result = false;
    }

    recoverInput(rawInput);
    Vector_remove(args);

    if(memFail) {
        return MEM_END;
    }
    return result;
}

Vector *_sanitizeInputRepairRoad(String *rawInput) {
    return _sanitizeInputDefault(rawInput);
}

int _validateInputsRepairRoad(Vector *inputs) {
    String *city1 = (String*)Vector_getElemById(inputs, 1);
    String *city2 = (String*)Vector_getElemById(inputs, 2);
    String *roadNewRepairYrStr = (String*)Vector_getElemById(inputs, 3);

    if(String_equals(city1, city2)) {
        return false;
    }
    String *intMaxStr = String_putInt(INT_MAX);
    String *intMinStr = String_putInt(INT_MIN);

    bool rez = (intMaxStr != NULL && intMinStr != NULL);
    bool memFail = false;
    if(!rez) {
        memFail = true;
    }

    if(rez && String_compareInts(roadNewRepairYrStr, intMaxStr) > 0) {
        rez = false;
    }
    if(rez && String_compareInts(roadNewRepairYrStr, intMinStr) < 0) {
        rez = false;
    }

    String_remove(intMaxStr);
    String_remove(intMinStr);

    if(memFail) {
        return MEM_END;
    }
    return rez;
}

int _executeRepairRoad(Map *map, Vector *args, String **output) {
    *output = NULL;
    return  repairRoad(map,
                    String_getRaw((String*)Vector_getElemById(args, 1)),
                    String_getRaw((String*)Vector_getElemById(args, 2)),
                    (int) String_toInt((String*)Vector_getElemById(args, 3))
    );
}