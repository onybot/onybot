#include "Arduino.h"
#include "command.h"

#ifndef menu_h
#define menu_h

#define MAX_COMMANDS 100


class Menu {

	public:
	//methods
	Menu();
	void runEvent(int event, int menuIndex, String lineTwoArray[], int arrayLenght, bool looping);
	//Attributes
	int index;
	bool selected;
	bool back;
	
	private:
	//Attributes
	
	//methods
};


#endif
