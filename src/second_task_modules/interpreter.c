/** @file
 * Implementacja interpretera 2 części zadania.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>

#include "interpreter.h"


static const size_t INITIAL_BUFFER_SIZE = 16;

Interpreter *Interpreter_new() {
    Interpreter *interpreter = malloc(sizeof(Interpreter));
    if(interpreter == NULL) {
        return NULL;
    }
    interpreter->currentLine = 0;
    return interpreter;
}

size_t Interpreter_getCurrentLine(Interpreter *interpreter) {
    return interpreter->currentLine;
}

void Interpreter_remove(void *interpreter) {
    Interpreter *del = (Interpreter*) interpreter;
    free(del);
}


String *Interpreter_getLine(Interpreter *interpreter) {
    char *buffer;
    size_t bufferSize = INITIAL_BUFFER_SIZE;
    bool isComment;
    buffer = malloc(bufferSize * sizeof(char));
    do {
        if (getline(&buffer, &bufferSize, stdin) == EOF) {
            free(buffer);
            return NULL;
        }
        isComment = (buffer[0] == '#' || buffer[0] == '\n');
        (interpreter->currentLine)++;
    } while (isComment);

    String *rez = String_new(buffer);
    free(buffer);
    return rez;
}
