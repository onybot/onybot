#include "Arduino.h"
#include "fsm.h"
#include "event.h"
#include "constants.h"
#include "command.h"
#include "menu.h"
#include "program.h"


void Fsm::init(){
	_setState(INITIAL_STATE);
	_wait = false;
	automaticLight = true;
}


bool Fsm::runEvent(int event){
	bool previous;
	previous = _currentState;
	switch (_currentState){
		case MAIN_STATE:
		{
			_runEventMain(event);
			break;
		}
		case WELCOME_STATE:
		{
			_runEventWelcome(event);
			break;
		}
		case PROGRAM_STATE:
		{
			_runEventProgram(event);
			break;
		}
		case VIEW_STATE:
		{
			_runEventView(event);
			break;
		}
		case DELETE_STATE:
		{
			_runEventDelete(event);
			break;
		}
		case VERSION_STATE:
		{
			_runEventVersion(event);
			break;
		}
		case RUN_STATE:
		{
			_runEventRun(event);
			break;
		}


	}
	return _changedLine;
}


void Fsm::_setState(int state){
	switch (state) {
		case WELCOME_STATE:
		{
			_setWelcome();
			break;
		}
		case MAIN_STATE:
		{
			_setMain();
			break;
		}
	}
}



////////////////////////////////////////////
// WELCOME
////////////////////////////////////////////

void Fsm::_runEventWelcome(int event){
	int timeCondition;
	timeCondition = millis() - _startState;
	_changedLine = true;
	if(timeCondition > WELCOME_TIME || event != BTN_NONE){
		_setMain();
		return;
	}
	_changedLine = false;
}


void Fsm::_setWelcome(){
	_currentState = WELCOME_STATE;
	firstLine = WELCOME_STRING_1;
	secondLine = WELCOME_STRING_2;
	_changedLine = true;
	_startState = millis();
}


////////////////////////////////////////////
// MAIN
////////////////////////////////////////////


void Fsm::_setMain(){
	Serial.println("set main menu");
	_currentState = MAIN_STATE;
	firstLine = MENU_STRING_1;
	_menuIndex = -1;
	_runEventMain(BTN_NONE);
	_changedLine = true;
}


void Fsm::_runEventMain(int event){
	Menu menu;
	int arrayLenght;
	int i;
	arrayLenght = (int) sizeof(MAIN_MENU_STRING_2)/sizeof(String);
	String strArray[arrayLenght];
	for(i=0; i<arrayLenght; i++){
		strArray[i] = MAIN_MENU_STRING_2[i];
	}

	menu.runEvent(event, _menuIndex, strArray, arrayLenght, true);


	if (menu.selected == true){
		// PROGRAM
		if (strArray[menu.index] == MAIN_MENU_PROGRAM){
			return _setProgram();
		// VIEW
		} if (strArray[menu.index] == MAIN_MENU_VIEW){
			return _setView();
		
		// DELETE
		} if (strArray[menu.index] == MAIN_MENU_DELETE){
			return _setDelete();
		
		// RUN
		} else if (strArray[menu.index] == MAIN_MENU_RUN){
			return _setRun();

		//VERSION
		} else if (strArray[menu.index] == MAIN_MENU_VERSION){
			return _setVersion();
		}
	} else {
		if (menu.index >= 0){
			_changedLine = true;
			secondLine = String(menu.index + 1, DEC) + MENU_SEPARATOR + strArray[menu.index];
			_menuIndex = menu.index;
		} else {
			_changedLine = false;
		}
	}
}







////////////////////////////////////////////
// PROGRAM
////////////////////////////////////////////
void Fsm::_setProgram(){
	_currentState = PROGRAM_STATE;
	firstLine = PROGRAM_STRING_1;
	_menuIndex = -1;
	_runEventProgram(BTN_NONE);
	_changedLine = true;
}


void Fsm::_runEventProgram(int event){
	Menu menu;
	int arrayLenght;
	int i;

	if (_wait == true){
		_wait = false;
		delay(PROGRAM_WAIT);
		_setProgram();
		return;

	}

	// update strings
	arrayLenght = (int) sizeof(PROGRAM_MENU_STRING_2)/sizeof(String);
	String strArray[arrayLenght];
	for(i=0; i<arrayLenght; i++){
		strArray[i] = PROGRAM_MENU_STRING_2[i];
	}
	_wait = false;
	// get menu selected
	menu.runEvent(event, _menuIndex, strArray, arrayLenght, true);
	if (menu.back == true){
		_setMain();
	} else if (menu.selected == true){
		program.addCommand(strArray[menu.index]);
		firstLine = PROGRAM_WAIT_STRING_1;
		secondLine = strArray[menu.index];
		_changedLine = true;
		_wait = true;
		
	} else {
		if (menu.index >= 0){
			_changedLine = true;
			secondLine = strArray[menu.index];
			_menuIndex = menu.index;
		} else {
			_changedLine = false;
		}
	}
}


////////////////////////////////////////////
// VIEW
////////////////////////////////////////////

void Fsm::_setView(){
	Serial.println("set view");
	_currentState = VIEW_STATE;
	firstLine = VIEW_STRING_1;
	_menuIndex = -1;
	_runEventView(BTN_NONE);
	_changedLine = true;
}

void Fsm::_runEventView(int event){
	//definitions
	Menu menu;
	Command cmd;
	int arrayLenght;
	int numCommands;
	int i;
	numCommands = program.getNumCommads();
	if (numCommands == 0){
		arrayLenght = 1;
	} else {
		arrayLenght = numCommands;
	}
	String strArray[arrayLenght];


	// create menu string array
	if (numCommands == 0){
		strArray[0] = VIEW_STRING_EMPTY;
	} else {
		for(i=0; i<arrayLenght; i++){
			cmd = program.getCommand(i);
			strArray[i] = cmd.id;
		}
	}

	// get menu selected
	menu.runEvent(event, _menuIndex, strArray, arrayLenght, false);

	if (menu.back == true){
		_setMain();
	} else if (menu.selected == true){
		//delete?
	} else {
		if (menu.index >= 0){
			_changedLine = true;
			if (numCommands == 0){
				secondLine = strArray[menu.index]; 
			} else {
				secondLine = String(menu.index + 1, DEC) + MENU_SEPARATOR + strArray[menu.index];
			}
			_menuIndex = menu.index;
		} else {
			_changedLine = false;
		}
	}
}


////////////////////////////////////////////
// DELETE
////////////////////////////////////////////

void Fsm::_setDelete(){
	_currentState = DELETE_STATE;
	firstLine = DELETE_STRING_1;
	secondLine = DELETE_STRING_2;
	_changedLine = true;
	_startState = millis();
	program.clear();
}

void Fsm::_runEventDelete(int event){
	int timeCondition;
	timeCondition = millis() - _startState;
	_changedLine = true;
	if(timeCondition > DELETE_TIME || event != BTN_NONE){
		_setMain();
		return;
	}
	_changedLine = false;
}

////////////////////////////////////////////
// VERSION
////////////////////////////////////////////

void Fsm::_setVersion(){
	_currentState = VERSION_STATE;
	firstLine = VERSION_STRING_1;
	secondLine = VERSION_STRING_2;
	_changedLine = true;
	_startState = millis();
}

void Fsm::_runEventVersion(int event){
	int timeCondition;
	timeCondition = millis() - _startState;
	_changedLine = true;
	if(timeCondition > VERSION_TIME || event != BTN_NONE){
		_setMain();
		return;
	}
	_changedLine = false;
}



////////////////////////////////////////////
// RUN
////////////////////////////////////////////

void Fsm::_setRun(){
	Serial.println("set run");
	_currentState = RUN_STATE;
	firstLine = RUN_STRING_1;
	secondLine = RUN_STRING_2;
	_changedLine = true;
	_startState = millis();
	automaticLight = false;
}

void Fsm::_runEventRun(int event){
	Command cmd;
	String previous;

	cmd = program.run();
	if (cmd.empty == false){
		previous = secondLine;
		if (secondLine != cmd.info){
			secondLine = cmd.info;
			_changedLine = true;
		} else {
			_changedLine = false;
		}
	} else {
		automaticLight = true;
		_setMain();
		return;
	}
	
}


