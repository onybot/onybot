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

////////////////////////////////////////////
// WELCOME
////////////////////////////////////////////

void Fsm::_runEventWelcome(int event){
	
	int timeCondition;
	timeCondition = millis() - _start;
	Serial.println("##########");
	Serial.println(WELCOME_TIME);
	Serial.println(timeCondition);
	_changedLine = true;
	if(timeCondition > WELCOME_TIME || event != BTN_NONE){
		Serial.println("condition");
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
	_start = millis();
}


////////////////////////////////////////////
// MAIN
////////////////////////////////////////////
void Fsm::_runEventMain(int event){
	
	int previous;
	int numStrings;

	numStrings = sizeof(MENU_STRING_2)/sizeof(String);
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
			
		}
		if (_menuIndex  < 0 ){
			_menuIndex = numStrings - 1;
		}
		_menuIndex = _menuIndex % numStrings;		
	}
	
	// update line and set for rewriting
	if(previous != _menuIndex){
		aux = MENU_STRING_2[_menuIndex];
		secondLine = aux;
		aux = _menuIndex;
		secondLine = aux + "-> " + secondLine;

		_changedLine = true;
	} else {
		_changedLine = false;
	}

	
	aux = MENU_STRING_2[_menuIndex];
	secondLine = aux;
	aux = _menuIndex;
	secondLine = aux + " -> " + secondLine;
	
	if(previous != _menuIndex){
		_changedLine = true;
	} else {
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