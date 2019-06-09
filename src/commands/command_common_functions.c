/** @file
 * Implementacja zbioru funckji implementowanych przez część komęnd.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 11.05.19
 */

#include "command_common_functions.h"

Vector *preprocessInput(String *inputStr) {
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

void recoverInput(String *inputStr) {
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

bool isNumeric(const char *input) {
	bool isNegative = (input[0] == '-');
	const char *inputTmp = input + isNegative;
	if(inputTmp[0] == '\0') {
		return false;
	}
	if(inputTmp[0] == '0' && (isNegative || inputTmp[1] != '\0')) {
		return false;
	}
	for(unsigned int i = 0; inputTmp[i] != '\0'; i++) {
		if(inputTmp[i] == '-' && isNegative) {
			return false;
		}
		else if(inputTmp[i] < '0' || inputTmp[i] > '9') {
			return false;
		}
	}
	return true;
}

Vector *_sanitizeInputDefault(String *rawInput) {
	Vector *argsString = Vector_new(String_remove);
	Vector *args = preprocessInput(rawInput);
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
	recoverInput(rawInput);

	return argsString;
}