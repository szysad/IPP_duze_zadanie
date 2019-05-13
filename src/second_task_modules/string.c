//
// Created by szysad on 05.05.19.
//

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

bool String_concatinate(String *string, String *addedString) {
    unsigned int newLen = string->length + addedString->length - 2;
    string->body = realloc(string->body, (newLen + 1) * sizeof(char));
    if(string->body == NULL) {
        return false;
    }
    string->length = newLen;
    strcat(string->body, addedString->body);
    string->body[newLen] = '\0';
    String_remove(addedString);
    return true;
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
    int long diff = String_toInt(string1) - String_toInt(string2);
    if (diff < 0) {
        return -1;
    }
    else if (diff > 0) {
        return 1;
    }
    else {
        return 0;
    }
}

String *String_putInt(long int input) {
    int count = 0;
    int minusChar = (input <= 0);
    long int tmp = input;
    while (tmp != 0) {
        tmp /= 10;
        ++count;
    }
    char *text = malloc((count + 1 + minusChar) * sizeof(char));
    if(text == NULL) {
        return NULL;
    }
    if(sprintf(text, "%ld", input) < 0) {
        free(text);
        return NULL;
    }
    String *newStr = String_new(text);
    free(text);
    return newStr;
}


bool String_isEmpty(String *string) {
    return (String_getLength(string) == 1 && String_getRaw(string)[0] == '\0');
}