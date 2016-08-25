#include "Arduino.h"
#include "command.h"

#ifndef program_h
#define program_h

#define MAX_COMMANDS 100


class Program {

	public:
	//methods
	Program();
	bool addCommand(String str);
	Command run();
	int getNumCommads();
	Command getCommand(int index);
	void clear();

	//Attributes

	private:
	//Attributes
	Command _commands[MAX_COMMANDS];
	int _programIndex;
	int _runIndex;
	bool running;
	int _currentCommand;

	//methods
	
	Command runCommand(int index);
};


#endif
