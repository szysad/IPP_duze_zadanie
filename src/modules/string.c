//
// Created by szysad on 05.05.19.
//

#include "string.h"
#include <stdlib.h>
#include <string.h>

String *String_new(char *charArr) {
    String *new = malloc(sizeof(String));
    if(new == NULL) {
        return NULL;
    }
    new->length = strlen(charArr) + 1;
    new->body = malloc(sizeof(new->length * sizeof(char)));
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