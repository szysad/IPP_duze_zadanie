/** @file
 * Implementacja interfejsu modułu string.h
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 05.05.19
 */

#include "string.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

String *String_new(char *charArr) {
	String *new = malloc(sizeof(String));
	if(new == NULL) {
		return NULL;
	}
	new->length = strlen(charArr) + 1;
	new->body = malloc(new->length * sizeof(char));
	if(new->body == NULL) {
		return NULL;
	}
	strcpy(new->body, charArr);
	return new;
}

void String_remove(void *string) {
	String *str = string;
	free(str->body);
	free(str);
}

char *String_getRaw(String *string) {
	return string->body;
}

size_t String_getLength(String *string) {
	return string->length;
}

void String_print(void *string) {
	String *s = (String*) string;
	printf("%s\n", s->body);
}

bool String_equals(String *string1, String *string2) {
	return (strcmp(string1->body, string2->body) == 0);
}

long int String_toInt(String *string) {
	char *tmp;
	return strtol(String_getRaw(string), &tmp, 10);
}

int String_compareInts(String *string1, String *string2) {
	bool isS1Negative = (String_getRaw(string1)[0] == '-');
	bool isS2Negative = (String_getRaw(string2)[0] == '-');
	if(!isS1Negative && isS2Negative) {
		return 1;
	}
	else if(isS1Negative && !isS2Negative) {
		return -1;
	}
	char *abs1 = String_getRaw(string1) + isS1Negative;
	char *abs2 = String_getRaw(string2) + isS2Negative;
	int result = 0;
	unsigned i;
	for(i = 0; abs1[i] != '\0' && abs2[i] != '\0'; i++) {
		if(result == 0 && (int) abs1[i] > (int) abs2[i]) {
			result = 1;
		}
		else if(result == 0 && (int) abs1[i] < (int) abs2[i]) {
			result = -1;
		}
	}
	if(abs1[i] != '\0' && abs2[i] == '\0') {
		result = 1;
	}
	else if(abs1[i] == '\0' && abs2[i] != '\0') {
		result = -1;
	}

	if(isS1Negative) {
		return -result;
	}
	return result;
}

String *String_putInt(long int input) {
	static const int LONG_INT_SIZE = 21;
	char text[LONG_INT_SIZE];
	if(sprintf(text, "%ld", input) < 0) {
		free(text);
		return NULL;
	}
	String *newStr = String_new(text);
	return newStr;
}