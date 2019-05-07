#include "map.h"


#include "second_task_modules/list.h"
#include "second_task_modules/string.h"
#include "second_task_modules/command.h"


int main() {

    Vector *commands = Vector_new(Command_remove);
    /* adding commands ...
     * .
     * .
     * .
     * */

    /* Interpreter *interpreter = Interpreter_new()
     * Interpreter_readLine(interpreter)*/
    char *rawInput = Interpreter_getLine(interpreter);
    bool isCommandMatched = false;
    Command *currentCmd = NULL;
    for(size_t i = 0; i < Vector_getSize(commands) && !isCommandMatched; i++) {
        Command *currentCmd = (Command*) Vector_getElemById(commands, i);
        if(Command_doesRawInputMatchTemplate(currentCmd, rawInput)) {
            isCommandMatched = true;
        }
    }
    if(!isCommandMatched) {
        //TODO Error handling: no command matched.
    }
    if(!Command_validateInput(currentCmd, rawInput)) {
        //TODO Error handling: cant allocate memory or invalid input.
    }
    free(rawInput);
    return Command_execute(currentCmd, map);
}