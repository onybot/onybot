#include "Arduino.h"

#ifndef program_h
#define program_h

#define MAX_COMMANDS 100

struct COMMAND {
	int next;
	String id;
};

class Program {

	public:
	//methods
	Program();
	bool addCommand(String str);

	int getNumCommads();
	COMMAND getCommand(int index);
	void clear();
	//attributes

	private:
	//Attributes
	COMMAND _commands[MAX_COMMANDS];
	int _commandIndex;
	//methods
	void run();
	void runCommand(COMMAND cmd);
};


#endif
