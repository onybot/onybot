#include "Arduino.h"

#ifndef program_h
#define program_h

#define MAX_COMMANDS 100

struct COMMAND {
	int next;
	String id;
	String info;
	bool empty;
};

class Program {

	public:
	//methods
	Program();
	bool addCommand(String str);
	COMMAND run();
	int getNumCommads();
	COMMAND getCommand(int index);
	void clear();

	//Attributes

	private:
	//Attributes
	COMMAND _commands[MAX_COMMANDS];
	int _programIndex;
	int _runIndex;
	bool running;
	int _currentCommand;

	//methods
	
	COMMAND runCommand(int index);
};


#endif
