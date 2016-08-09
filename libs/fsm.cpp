#include "Arduino.h"
#include "fsm.h"
#include "event.h"
#include "constants.h"
#include "command.h"
#include "program.h"


void Fsm::init(){
	_setState(INITIAL_STATE);
	_wait = false;
	automaticLight = true;
}


bool Fsm::run_event(int event){
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


String Fsm::_runEventMenu(int event, String lineTwoArray[], int arrayLenght, bool showIndex, bool looping){
	
	int previous;
	String aux;
	previous = _menuIndex;
	
	// first time
	if (_menuIndex == -1){
		_menuIndex = 0;
		_changedLine = true;
	} else {
		if (event == BTN_UP){
			_menuIndex = _menuIndex - 1;
			
		} else if (event == BTN_DOWN){	
			_menuIndex = _menuIndex + 1;
			
		} else if (event == BTN_SELECT || event == BTN_RIGHT){
			// change state
			return lineTwoArray[_menuIndex];
		} else if (event == BTN_LEFT){
			// change state
			return BACK_STRING;
		}
		if (_menuIndex < 0 ){
			if (looping == true){
				_menuIndex = arrayLenght - 1;
			} else {
				_menuIndex = 0;
			}
		}
		if (_menuIndex > arrayLenght - 1){
			if (looping == true){
				_menuIndex = 0;
			} else {
				_menuIndex = arrayLenght - 1;
			}
		}
		_menuIndex = _menuIndex % arrayLenght;
	}
	
	// update line and set for rewriting
	if(previous != _menuIndex){
		if (showIndex == true){
			aux = lineTwoArray[_menuIndex];
			secondLine = aux;
			aux = _menuIndex + 1;
			secondLine = aux + MENU_SEPARATOR + secondLine;
		} else {
			secondLine = lineTwoArray[_menuIndex];
		}
		return CHANGE_STRING;
	} else {
		return NO_CHANGE_STRING;
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
void Fsm::_runEventMain(int event){
	String menuResponse;
	int arrayLenght;
	int i;
	arrayLenght = (int) sizeof(MAIN_MENU_STRING_2)/sizeof(String);
	String strArray[arrayLenght];
	for(i=0; i<arrayLenght; i++){
		strArray[i] = MAIN_MENU_STRING_2[i];
	}
	menuResponse = _runEventMenu(event, strArray, arrayLenght, true, true);

	// update display
	if (menuResponse == NO_CHANGE_STRING){
		_changedLine = false;
	} else if (menuResponse == CHANGE_STRING){
		_changedLine = true;

	// PROGRAM
	} if (menuResponse == MAIN_MENU_PROGRAM){
		return _setProgram();
	
	// VIEW
	} if (menuResponse == MAIN_MENU_VIEW){
		return _setView();
	
	// DELETE
	} if (menuResponse == MAIN_MENU_DELETE){
		return _setDelete();
	
	// RUN
	} else if (menuResponse == MAIN_MENU_RUN){
		return _setRun();

	//VERSION
	} else if (menuResponse == MAIN_MENU_VERSION){
		return _setVersion();
	}

}


void Fsm::_setMain(){
	_currentState = MAIN_STATE;
	firstLine = MENU_STRING_1;
	_menuIndex = -1;
	_runEventMain(BTN_NONE);
	_changedLine = true;
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
	String menuResponse;
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

	// get menu selected
	menuResponse = _runEventMenu(event, strArray, arrayLenght, false, true);

	if (menuResponse == NO_CHANGE_STRING){
		_wait = false;
		_changedLine = false;

	} else if (menuResponse == CHANGE_STRING){
		_wait = false;
		_changedLine = true;
	} else if (menuResponse == BACK_STRING){
		_setMain();
	} else {
		program.addCommand(menuResponse);
		firstLine = PROGRAM_WAIT_STRING_1;
		secondLine = menuResponse;
		_changedLine = true;
		_wait = true;
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

	String menuResponse;
	Command cmd;
	int arrayLenght;
	int i;
	bool showIndex;

	// update strings
	arrayLenght = program.getNumCommads();

	if (arrayLenght == 0){
		showIndex = false;
		String strArray[1];
		strArray[i] = VIEW_STRING_EMPTY;
		// get menu selected
		menuResponse = _runEventMenu(event, strArray, arrayLenght, showIndex, false);
	} else {
		String strArray[arrayLenght];
		showIndex = true;
		for(i=0; i<arrayLenght; i++){
			cmd = program.getCommand(i);
			strArray[i] = cmd.id;
		}
		// get menu selected
		menuResponse = _runEventMenu(event, strArray, arrayLenght, showIndex, false);
	}

	if (menuResponse == NO_CHANGE_STRING ){
		_changedLine = false;
	} else if (menuResponse == CHANGE_STRING && arrayLenght > 0){
		_changedLine = true;
	} else if (menuResponse == BACK_STRING){
		_setMain();
	}else{
		_changedLine = false;
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


