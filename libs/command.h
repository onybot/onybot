#include "Arduino.h"

#ifndef command_h
#define command_h

/*struct COMMAND {
	int next;
	String id;
	String info;
	bool empty;
};*/

class Command {

	public:
	//methods
	Command();
	void run();

	//Attributes
	String id;
	String info;
	bool empty;
	private:
	//Attributes
	//methods
};


#endif
