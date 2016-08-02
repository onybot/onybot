#include "Arduino.h"
#include "fsm.h"
#include "event.h"
#include "constants.h"


void Fsm::init(){
  _setState(INITIAL_STATE);
  
}


void Fsm::run_event(int event){
  switch (_currentState)
  {
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
}


void Fsm::_runEventMain(int event){

};

void Fsm::_runEventWelcome(int event){
	delay(WELCOME_TIME);
	_setMain();
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


void Fsm::_setWelcome(){
	_currentState=WELCOME_STATE;
	firstLine = WELCOME_STRING_1;
	secondLine = WELCOME_STRING_2;
}

void Fsm::_setMain(){
	_currentState=WELCOME_STATE;
	firstLine = "test 1";
	secondLine = "test 2";
}