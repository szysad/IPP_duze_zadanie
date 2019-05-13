/** @file
 * Implementacja zbioru funkcji komendy wykonującą operację newCustomRoute na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 08.05.19
 */

#include "command_newCustomRoute.h"
#include "command_common_functions.h"
#include "string.h"
static const int MEM_END = -1;
static const size_t MINIMUM_ARGS_EXPECTED = 4;
static const int VECTOR_ELEM_CYCLE = 3;


int _doesRawInputMatchNewCustomRoute(String *rawInput) {
    Vector *args = preprocessInput(rawInput);
    bool result = (args != NULL);
    bool memFail = (args == NULL);
    if(memFail) {
        return MEM_END;
    }
    if(Vector_getSize(args) < MINIMUM_ARGS_EXPECTED) {
        Vector_remove(args);
        return 0;
    }
    if(!isNumeric((char*)Vector_getElemById(args, 0))) {
        Vector_remove(args);
        return 0;
    }
    /* starting from i = 1, because we exclude first param which is routeId */
    int counter = 0;
    for(size_t i = 1; i < Vector_getSize(args) && result; i++) {
        char *arg = (char*) Vector_getElemById(args, i);
        switch (counter) {
            case 0 :
                result = result && City_isNameValid(arg);
                break;
            case 1 :
                result = result && isNumeric(arg);
                break;
            case 2 :
                result = result && isNumeric(arg);
                break;
        }
        counter++;
        if(counter == VECTOR_ELEM_CYCLE) {
            counter = 0;
        }
    }
    /* route description has to end by city_name */
    if(counter != 1) {
        result = 0;
    }

    recoverInput(rawInput);
    Vector_remove(args);

    return result;
}

Vector *_sanitizeInputNewCustomRoute(String *rawInput) {
    return _sanitizeInputDefault(rawInput);
}

int _validateInputsNewCustomRoute(Vector *input) {
    bool result;
    String *intMaxStr = String_putInt(INT_MAX);
    String *intMinStr = String_putInt(INT_MIN);
    String *uintMaxStr = String_putInt(UINT_MAX);
    String *uintMinStr = String_putInt(0);

    result = (intMaxStr != NULL && intMinStr != NULL && uintMaxStr != NULL && uintMinStr != NULL);


    /* check if there are any duplicates of cities in vector */
    for(size_t i = 1; i < Vector_getSize(input) && result; i += VECTOR_ELEM_CYCLE) {
        String *city = (String*) Vector_getElemById(input, i);
        for(size_t j = i + VECTOR_ELEM_CYCLE; j < Vector_getSize(input) && result; j += VECTOR_ELEM_CYCLE) {
            if(String_equals((city), (String*) Vector_getElemById(input, j))) {
                result = false;
            }
        }
    }
    /* check if road lengths are valid ~ range case */
    for(size_t i = 2; i < Vector_getSize(input) && result; i += VECTOR_ELEM_CYCLE ) {
        if(String_compareInts((String*) Vector_getElemById(input, i), uintMaxStr) > 0) {
            result = false;
        }
        if(String_compareInts((String*) Vector_getElemById(input, i), uintMinStr) < 0) {
            result = false;
        }
    }
    /* check if road build year are valid ~ range case */
    for(size_t i = 3; i < Vector_getSize(input) && result; i += VECTOR_ELEM_CYCLE ) {
        if(String_compareInts((String*) Vector_getElemById(input, i), intMaxStr) > 0) {
            result = false;
        }
        if(String_compareInts((String*) Vector_getElemById(input, i), intMinStr) < 0) {
            result = false;
        }
    }

    String_remove(intMaxStr);
    String_remove(intMinStr);
    String_remove(uintMaxStr);
    String_remove(uintMinStr);

    return result;
}

int _executeNewCustomRoute(Map *map, Vector *args, String **output) {
    *output = NULL;
    return newCustomRoute(map, args);

}