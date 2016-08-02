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
	_changedLine = true;
	if(millis() - _start > WELCOME_TIME || event != BTN_NONE){
		_setMain();
	}
}


void Fsm::_setWelcome(){
	_currentState=WELCOME_STATE;
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
	previous = _menuIndex;
	if (event == BTN_DOWN){
		_menuIndex = (_menuIndex + 1) % 3;
	}
	switch (_menuIndex) {
		case 0:
		{
			secondLine = MENU_STRING_2_A;
			break;
		}
		case 1:
		{
			secondLine = MENU_STRING_2_B;
			break;
		}
		case 2:
		{
			secondLine = MENU_STRING_2_C;
			break;
		}
	}
	secondLine = "-> " + secondLine;
	if(previous != _menuIndex){
		_changedLine = true;
	} else {
		_changedLine = false;
	}

}



void Fsm::_setMain(){
	_currentState=MAIN_STATE;
	firstLine = MENU_STRING_1;
	_menuIndex = 0;
	_runEventMain(BTN_NONE);
	_changedLine = true;
}