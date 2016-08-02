#include "Arduino.h"

#ifndef fsm_h
#define fsm_h

#define WELCOME_STATE 0
#define MAIN_STATE 1


#define INITIAL_STATE WELCOME_STATE




class Fsm {

	public:
	//methods
	void init();
	bool run_event(int event);

	//attributes
	String firstLine;
	String secondLine;


	private:


	//Attributes
	int _currentState;
	int _menuIndex;
	bool _changedLine;
	
	//methods
	void _welcomeState(int event);
	void _mainState(int event);
	void _setState(int event);
	void _setMain();
	void _setWelcome();
	void _runEventMain(int event);
	void _runEventWelcome(int event);

};


#endif
