/** @file
 * Implementacja zbioru funkcji komendy wykonującej operację addRoad na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 08.05.19
 */

#include "command_addRoad.h"
#include "command_common_functions.h"
#include <string.h>

static const unsigned int ARGS_EXPECTED = 5;
static const int MEM_END = -1;
static const char *KEYWORD = "addRoad";


int _doesRawInputMatchAddRoad(String *rawInput) {

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
    if(result && !isNumeric((char*)Vector_getElemById(args, 4))) {
        result = false;
    }

    recoverInput(rawInput);
    Vector_remove(args);

    if(memFail) {
        return MEM_END;
    }
    return result;
}

Vector *_sanitizeInputAddRoad(String *rawInput) {
    return _sanitizeInputDefault(rawInput);
}

int _validateInputsAddRoad(Vector *inputs) {
	String *city1 = (String*)Vector_getElemById(inputs, 1);
	String *city2 = (String*)Vector_getElemById(inputs, 2);
    String *roadLenStr = (String*)Vector_getElemById(inputs, 3);
    String *roadBuildYrStr = (String*)Vector_getElemById(inputs, 4);

    if(String_equals(city1, city2)) {
		return false;
	}
    String *intMaxStr = String_new("2147483647");
    String *intMinStr = String_new("-2147483648");

    bool rez = (intMaxStr != NULL && intMinStr != NULL);
    bool memFail = false;
    if(!rez) {
        memFail = true;
    }

	if(rez && String_compareInts(roadLenStr, intMaxStr) > 0) {
        rez = false;
    }
    if(rez && String_compareInts(roadLenStr, intMinStr) < 0) {
        rez = false;
    }
    if(rez && String_compareInts(roadBuildYrStr, intMaxStr) > 0) {
        rez = false;
    }
    if(rez && String_compareInts(roadBuildYrStr, intMinStr) < 0) {
        rez = false;
    }

	String_remove(intMaxStr);
	String_remove(intMinStr);

	if(memFail) {
        return MEM_END;
	}
	return rez;
}

int _executeAddRoad(Map *map, Vector *args, String **output) {
    *output = NULL;
	return addRoad(map,
                    String_getRaw((String*)Vector_getElemById(args, 1)),
                    String_getRaw((String*)Vector_getElemById(args, 2)),
					String_toInt((String*)Vector_getElemById(args, 3)),
					String_toInt((String*)Vector_getElemById(args, 4))
					);
}