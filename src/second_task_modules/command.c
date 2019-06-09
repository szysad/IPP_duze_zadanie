/** @file
 * Implementacja interfejsu Komendy.
 *
 * @author Szymon Sadkowski <ss406325@students.mimuw.edu.pl>
 * @date 06.05.19
 */

#include "command.h"
#define MEM_END -1


Command *Command_new(int (*doesRawInputMatchTemplate)(String *), Vector *(*sanitizeInputFunc)(String * ), int (*validateInputsFunc)(Vector *), int (*execute)(Map *, Vector *, String **output)) {
	Command *command = malloc(sizeof(Command));
	if(command == NULL) {
		return NULL;
	}
	command->isreadyToExecute = false;
	command->doesRawInputMatchTemplate = doesRawInputMatchTemplate;
	command->args = NULL;
	command->sanitizeInputFunc = sanitizeInputFunc;
	command->validateInputsFunc = validateInputsFunc;
	command->execute = execute;
	return command;
}

void Command_remove(void *command1) {
	Command *command = (Command*) command1;
	if(command->args != NULL) {
		Vector_remove(command->args);
	}
	free(command);
}

int Command_doesRawInputMatchTemplate(Command *command, String *rawInput) {
	return command->doesRawInputMatchTemplate(rawInput);
}

int Command_validateInput(Command *command, String *rawInput) {
	Vector *args = command->sanitizeInputFunc(rawInput);
	if(args == NULL) {
		return MEM_END;
	}
	if(!command->validateInputsFunc(args)) {
		Vector_remove(args);
		return false;
	}
	command->args = args;
	command->isreadyToExecute = true;
	return true;
}

int Command_execute(Command *command, Map *map) {
	assert(command->isreadyToExecute);
	String *output;
	int status = command->execute(map, command->args, &output);
	if(output != NULL) {
		String_print(output);
		String_remove(output);
	}
	return status;
}

void Command_reset(Command *command) {
	//TODO func Vector_reset()
	if(command->args != NULL) {
		Vector_remove(command->args);
	}
	command->args = NULL;
	command->isreadyToExecute = false;
}
