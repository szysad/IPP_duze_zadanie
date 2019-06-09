/** @file
 * Implementacja funkcji komendy wykonującą operację extendRoute na mapie.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */

#include "command_extendRoute.h"
#include "command_common_functions.h"
#include <string.h>

static const unsigned int ARGS_EXPECTED = 3;
static const int MEM_END = -1;
static const char *KEYWORD = "extendRoute";

int _doesRawInputMatchExtendRoute(String *rawInput) {
	Vector *args = preprocessInput(rawInput);
	bool result = (args != NULL);
	bool memFail = (args == NULL);
	result = result && (Vector_getSize(args) == ARGS_EXPECTED);
	result = result && (strcmp(KEYWORD, (char*) Vector_getElemById(args, 0)) == 0);
	result = result && isNumeric((char*) Vector_getElemById(args, 1));
	result = result && City_isNameValid((char*) Vector_getElemById(args, 2));
	recoverInput(rawInput);
	Vector_remove(args);
	if(memFail) {
		return MEM_END;
	}
	return result;
}

Vector *_sanitizeInputExtendRoute(String *rawInput) {
	return _sanitizeInputDefault(rawInput);
}

int _validateInputsExtendRoute(Vector *inputs) {
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

int _executeExtendRoute(Map *map, Vector *args, String **output) {
	*output = NULL;
	unsigned routeId = (unsigned) String_toInt((String*) Vector_getElemById(args, 1));
	const char* city = String_getRaw((String*) Vector_getElemById(args, 2));
	return extendRoute(map, routeId, city);
}