#include "map.h"
#include "second_task_modules/string.h"
#include "second_task_modules/command.h"
#include "second_task_modules/interpreter.h"

#include "commands/command_addRoad.h"
#include "commands/command_repairRoad.h"
#include "commands/command_getRouteDescription.h"
#include "commands/command_newCustomRoute.h"

#define ADD_COMMAND(vector, doesRowInputMatch, sanitizeInput, validateInput, execute) {\
	Command *cmd = Command_new(doesRowInputMatch, sanitizeInput, validateInput, execute);\
	if(cmd == NULL || !Vector_add(vector, cmd)) {\
		goto free_all;\
	}\
}

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

	ADD_COMMAND(commands, _doesRawInputMatchAddRoad, _sanitizeInputAddRoad, _validateInputsAddRoad, _executeAddRoad)
	ADD_COMMAND(commands, _doesRawInputMatchRepairRoad, _sanitizeInputRepairRoad, _validateInputsRepairRoad, _executeRepairRoad)
	ADD_COMMAND(commands,_doesRawInputMatchGetRouteDesc, _sanitizeInputGetRouteDesc, _validateInputsGetRouteDesc, _executeGetRouteDesc)
	ADD_COMMAND(commands, _doesRawInputMatchNewCustomRoute, _sanitizeInputNewCustomRoute, _validateInputsNewCustomRoute, _executeNewCustomRoute)

	String *rawInput;
	while ((rawInput = Interpreter_getLine(interpreter)) != NULL) {
		bool isCommandMatched = false;
		int status = 0;
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
		int status2;
		if (!isCommandMatched) {
			fprintf( stderr, "ERROR %lu\n", Interpreter_getCurrentLine(interpreter));
			status = 0;
		}
		if(status && (status2 = Command_validateInput(currentCmd, rawInput)) < 0) {
			goto free_all;
		}
		if (status && status2 == 0) {
			fprintf( stderr, "ERROR %lu\n", Interpreter_getCurrentLine(interpreter));
			status = 0;
		}
		if(status && (status2 = Command_execute(currentCmd, map)) < 0) {
			goto free_all;
		}
		if(status && status2 == 0) {
			fprintf( stderr, "ERROR %lu\n", Interpreter_getCurrentLine(interpreter));
		}
		Command_reset(currentCmd);
		String_remove(rawInput);
	}

	free_all:
	Interpreter_remove(interpreter);
	deleteMap(map);
	Vector_remove(commands);

	return 0;
}