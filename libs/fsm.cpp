#include "Arduino.h"
#include "fsm.h"
#include "event.h"
#include "constants.h"


void Fsm::init(){
	_setState(INITIAL_STATE);

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
	}
	if (_changedLine==true){
		Serial.println("change");
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


String Fsm::_runEventMenu(int event, String lineTwoArray[], int arrayLenght){
	
	int previous;
	String aux;
	previous = _menuIndex;
	
	// first time
	if (_menuIndex == -1){
		_menuIndex = 0;
		_changedLine = true;
	} else {
		if (event == BTN_UP){	
			_menuIndex = _menuIndex + 1;
			
		} else if (event == BTN_DOWN){	
			_menuIndex = _menuIndex - 1;
			
		} else if (event == BTN_SELECT || event == BTN_RIGHT ||event ==  BTN_LEFT){
			// change state
			return lineTwoArray[_menuIndex];
		}
		if (_menuIndex  < 0 ){
			_menuIndex = arrayLenght - 1;
		}
		_menuIndex = _menuIndex % arrayLenght;
	}
	
	// update line and set for rewriting
	if(previous != _menuIndex){
		aux = lineTwoArray[_menuIndex];
		secondLine = aux;
		aux = _menuIndex;
		secondLine = aux + "-> " + secondLine;
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
	arrayLenght = (int) sizeof(MENU_STRING_2)/sizeof(String);
	String strArray[arrayLenght];
	for(i=0; i<arrayLenght; i++){
		strArray[i] = MENU_STRING_2[i];
	}
	menuResponse = _runEventMenu(event, strArray, arrayLenght);
	if (menuResponse == NO_CHANGE_STRING){
		_changedLine = false;
	} else if (menuResponse == CHANGE_STRING){
		_changedLine = true;

	// PROGRAM
	} if (menuResponse == MENU_PROGRAM){
		return _setProgram();
	
	// RUN
	} else if (menuResponse == MENU_RUN){
		Serial.println(MENU_RUN);
		_changedLine = false;

	//VERSION
	} else if (menuResponse == MENU_VERSION){
		Serial.println(MENU_VERSION);
		_changedLine = false;
	}

}


void Fsm::_setMain(){
	Serial.println("set main");
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
	Serial.println("set program");
	_currentState = PROGRAM_STATE;
	firstLine = "PROGRAMING";
	secondLine = "PROGRAMING";
	_startState = millis();
	_changedLine = true;
}


void Fsm::_runEventProgram(int event){
	int timeCondition;
	timeCondition = millis() - _startState;
	if(timeCondition > WELCOME_TIME || event != BTN_NONE){
		_setMain();
		return;
	}
	_changedLine = false;
}
