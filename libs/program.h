#include "Arduino.h"

#ifndef program_h
#define program_h

#define MAX_COMMANDS 100


class Program {

	public:
	//methods
	Program();
	bool addCommand(String command);
	//attributes

	private:
	//Attributes
	int _commands[MAX_COMMANDS];
	int _commandIndex;
	//methods
};


#endif
