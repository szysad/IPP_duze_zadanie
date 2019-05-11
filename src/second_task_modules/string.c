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

int String_compareInts(String *string1, String *string2) {
    char *s1 = string1->body;
    char *s2 = string2->body;
    bool isS1positive = (s1[0] != '-');
    bool isS2positive = (s2[0] != '-');
    int absComp = 0;
    if(!isS1positive) {
        s1++;
    }
    if(!isS2positive) {
        s2++;
    }
    unsigned int i;
    for(i = 0; (s1[i] != '\0' && s2[i] != '\0'); i++) {
        if((int)s1[i] > (int)s2[i]) {
            absComp = 1;
        }
        else if((int)s1[i] < (int)s2[i]) {
            absComp = -1;
        }
    }
    if(s1[i] != '\0' && s2[i] == '\0') {
        absComp = 1;
    }
    else if(s1[i] == '\0' && s2[i] != '\0') {
        absComp = -1;
    }
    if(isS1positive && isS2positive) {
        return absComp;
    }
    else if(isS1positive && !isS2positive) {
        return 1;
    }
    else if(!isS1positive && isS2positive) {
        return -1;
    }
    else {
        return -absComp;
    }
}

int String_toInt(String *string) {
    bool isNegative = (string->body[0] == '-');
    if(isNegative) {
        return -atoi(string->body + 1);
    }
    else {
        return atoi(string->body);
    }
}