/** @file
 * Implementacja zbioru funkcji komendy wykonującą operację removeRoute na mapie.

 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */


#include "command_removeRoute.h"
#include "command_common_functions.h"
#include <string.h>

static const unsigned int ARGS_EXPECTED = 2;
static const int MEM_END = -1;
static const char *KEYWORD = "removeRoute";


int _doesRawInputMatchRemoveRoute(String *rawInput) {
	Vector *args = preprocessInput(rawInput);
	bool result = (args != NULL);
	bool memFail = (args == NULL);
	result = result && (Vector_getSize(args) == ARGS_EXPECTED);
	result = result && (strcmp(KEYWORD, (char*) Vector_getElemById(args, 0)) == 0);
	result = result && isNumeric((char*) Vector_getElemById(args, 1));
	recoverInput(rawInput);
	Vector_remove(args);
	if(memFail) {
		return MEM_END;
	}
	return result;
}

Vector *_sanitizeInputRemoveRoute(String *rawInput) {
	return _sanitizeInputDefault(rawInput);
}

int _validateInputsRemoveRoute(Vector *inputs) {
	bool result;
	bool memFail = false;
	String *routeId = (String*) Vector_getElemById(inputs, 1);
	String *uintMaxStr = String_putInt(UINT_MAX);
	String *uintMinStr = String_putInt(0);
	result = (uintMaxStr != NULL && uintMinStr != NULL);
	if(!result) {
		memFail = true;
	}
	result = result && (String_compareInts(routeId, uintMinStr) >= 0);
	result = result && (String_compareInts(routeId, uintMaxStr) <= 0);

	String_remove(uintMaxStr);
	String_remove(uintMinStr);
	if(memFail) {
		return MEM_END;
	}
	return result;
}

int _executeRemoveRoute(Map *map, Vector *args, String **output) {
	*output = NULL;
	unsigned routeId = (unsigned) String_toInt((String*) Vector_getElemById(args, 1));

	return removeRoute(map, routeId);
}
