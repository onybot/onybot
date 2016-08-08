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
	int commands[MAX_COMMANDS];
	//methods
};


#endif
