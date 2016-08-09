#include "Arduino.h"
#include "program.h"



Program::Program(){
	_commandIndex = 0;
}


bool Program::addCommand(String str){
	COMMAND cmd;
	cmd.next = -1;
	cmd.id = str;
	_commands[_commandIndex] = cmd;
	_commandIndex++;
	if (_commandIndex > MAX_COMMANDS){
		_commandIndex = 0;
	}
	Serial.println(cmd.id);
	return true;
}


void Program::run(){
	int i;
	for(i=0; i<_commandIndex; i++){
		runCommand(_commands[i]);
	}
}

void  Program::runCommand(COMMAND cmd){
}