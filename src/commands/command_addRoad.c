/** @file
 * Implementacja funkcji komendy wykonującej operację addRoad na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 08.05.19
 */

#include "command_addRoad.h"
#include <string.h>

static const unsigned int ARGS_EXPECTED = 5;
static const int MEM_END = -1;

static Vector *preprocessInput(String *inputStr) {
    Vector *inputsPtrs = Vector_new(NULL);
    if(inputsPtrs == NULL) {
        return NULL;
    }
    unsigned int len = String_getLength(inputStr);
    char *input = String_getRaw(inputStr);
    if(len > 0) {
        if(!Vector_add(inputsPtrs, String_getRaw(inputStr))) {
            Vector_remove(inputsPtrs);
            return NULL;
        }
    }
    for(unsigned int i = 0; i < len; i++) {
        if(input[i] == ';' || input[i] == '\n') {
            input[i] = '\0';
            if(input[i + 1] != '\0') {
                if(!Vector_add(inputsPtrs, &input[i + 1])) {
                    Vector_remove(inputsPtrs);
                    return NULL;
                }
            }
        }
    }
    return inputsPtrs;
}

static void recoverInput(String *inputStr) {
    unsigned int len = String_getLength(inputStr);
    char *input = String_getRaw(inputStr);
    for(unsigned int i = 0; i < len; i++) {
        if(input[i] == '\0' && i != len - 1) {
            if(i == len - 2) {
                input[i] = '\n';
            }
            else {
                input[i] = ';';
            }
        }
    }
}

static bool isNumeric(const char *input) {
    for(unsigned int i = 0; input[i] != '\0'; i++) {
        if(input[i] == '-') {
            if(i != 0) {
                return false;
            }
        }
        else if(input[i] < '0' || input[i] > '9') {
            return false;
        }
    }
    return true;
}


int doesRawInputMatchTemplateAddRoad(String *input) {

    char *KEYWORD = "addRoad";
	Vector *args = preprocessInput(input);
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

    recoverInput(input);
    Vector_remove(args);

    if(memFail) {
        return MEM_END;
    }
    return result;
}

Vector *sanitizeInputFuncAddRoad(String *input) {

	Vector *argsString = Vector_new(String_remove);

	Vector *args = preprocessInput(input);
	if(args == NULL) {
	    Vector_remove(argsString);
        return NULL;
	}

    for(size_t i = 0; i < Vector_getSize(args); i++) {
        String *new = String_new((char*)Vector_getElemById(args, i));
        if(new == NULL || !Vector_add(argsString, new)) {
            Vector_remove(argsString);
            return NULL;
        }
    }

    Vector_remove(args);
	recoverInput(input);

	return argsString;
}

int validateInputsFuncAddRoad(Vector *inputs) {
	String *city1 = (String*)Vector_getElemById(inputs, 1);
	String *city2 = (String*)Vector_getElemById(inputs, 2);
    String *roadLenStr = (String*)Vector_getElemById(inputs, 3);
    String *roadBuildYrStr = (String*)Vector_getElemById(inputs, 4);

    if(String_equals(city1, city2)) {
		return false;
	}
    String *intMaxStr = String_new("2147483647");
    String *intMinStr = String_new("-2147483648");
    String *zeroStr = String_new("0");

    bool rez = (intMaxStr != NULL && intMinStr != NULL && zeroStr != NULL);
    bool memFail = false;
    if(!rez) {
        memFail = true;
    }

    if(rez && String_compareInts(roadLenStr, zeroStr) <= 0) {
        rez = false;
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
    if(rez && String_compareInts(roadBuildYrStr, zeroStr) == 0) {
        rez = false;
    }

	String_remove(intMaxStr);
	String_remove(intMinStr);
	String_remove(zeroStr);

	if(memFail) {
        return MEM_END;
	}
	return rez;
}

bool executeAddRoad(Map *map, Vector *args) {
    for(size_t i = 0; i < args->size; i++) {
        String_print((String*)Vector_getElemById(args, i));
    }
	return  addRoad(map,
                    String_getRaw((String*)Vector_getElemById(args, 1)),
                    String_getRaw((String*)Vector_getElemById(args, 2)),
					String_toInt((String*)Vector_getElemById(args, 3)),
					String_toInt((String*)Vector_getElemById(args, 4))
					);
}