#include "Arduino.h"
#include "program.h"
#include "constants.h"



Program::Program(){
	_programIndex = 0;
	running = false;
	_runIndex = 0;
}


bool Program::addCommand(String str){
	COMMAND cmd;
	cmd.next = -1;
	cmd.id = str;
	cmd.info = str;
	cmd.empty = false;
	_commands[_programIndex] = cmd;
	_programIndex++;
	if (_programIndex > MAX_COMMANDS){
		_programIndex = 0;
	}
	return true;
}


COMMAND Program::run(){
	COMMAND cmd;
	if (running == false){
		running = true;
		_runIndex = 0;
		_currentCommand = -1;
	}
	if (_runIndex <= _programIndex && _programIndex > 0){
		cmd = runCommand(_runIndex);
	} else {
		running = false;
		cmd.empty = true;
	}
	return cmd;
}

COMMAND Program::runCommand(int index){

	COMMAND cmd;
	cmd = _commands[index];
	if (_currentCommand != index){
		// run command first time
		// do nothing, show command info
		_currentCommand = index;
	} else {
		// not first time. run command actually
		// run command
		delay(COMMAND_TEST_DELAY);

		// next command;
		_runIndex ++;
	}
	return cmd;
}


int Program::getNumCommads(){
	return _programIndex;
}

COMMAND Program::getCommand(int index){
	return _commands[index];
}

void Program::clear(){
	_programIndex = 0;
}
