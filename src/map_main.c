#include "map.h"
#include "second_task_modules/list.h"
#include "second_task_modules/string.h"
#include "second_task_modules/command.h"
#include "second_task_modules/interpreter.h"

#include "commands/command_addRoad.h"


int main() {

    Interpreter *interpreter = Interpreter_new();
    if(interpreter == NULL) {
        return 0;
    }
    Map *map = newMap();
    if(map == NULL) {
        Interpreter_remove(interpreter);
        return 0;
    }
    Vector *commands = Vector_new(Command_remove);
    if(commands == NULL) {
        Interpreter_remove(interpreter);
        deleteMap(map);
        return 0;
    }

    Command *cmd = Command_new(doesRawInputMatchTemplateAddRoad, validateInputsFuncAddRoad, sanitizeInputFuncAddRoad, executeAddRoad);
    if(cmd == NULL || !Vector_add(commands, cmd)) {
        goto free_all;
    }


    String *rawInput;
    while ((rawInput = Interpreter_getLine(interpreter)) != NULL) {
        bool isCommandMatched = false;
        int status;
        Command *currentCmd = NULL;
        for (size_t i = 0; i < Vector_getSize(commands) && !isCommandMatched; i++) {
            currentCmd = (Command *) Vector_getElemById(commands, i);
            status = Command_doesRawInputMatchTemplate(currentCmd, rawInput);
            if (status >= 0) {
                isCommandMatched = (status > 0);
            }
            else {
                /* free all memory, end program */
                goto free_all;
            }
        }
        if (!isCommandMatched) {
            printf("syntax error on line: %lu\n", Interpreter_getCurrentLine(interpreter));
            status = 0;
        }
        if (status && !Command_validateInput(currentCmd, rawInput)) {
            printf("list validation error on line: %lu\n", Interpreter_getCurrentLine(interpreter));
            status = 0;
        }
        if(status && !Command_execute(currentCmd, map)) {
            printf("execution error in line: %lu\n", Interpreter_getCurrentLine(interpreter));
            status = 0;
        }
        Command_reset(currentCmd);
        String_remove(rawInput);
        if(status) {
            Map_print(map);
        }
    }
    free_all:
    Interpreter_remove(interpreter);
    deleteMap(map);
    Vector_remove(commands);

    return 0;
}