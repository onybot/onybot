#include "Arduino.h"
#include "program.h"



Program::Program(){
	_commandIndex = 0;
}


bool Program::addCommand(String command){
	_commands[_commandIndex] = command;
	_commandIndex++;
	if (_commandIndex > MAX_COMMANDS){
		_commandIndex = 0;
	}
	Serial.println(command);
	return true;
}