#include "Arduino.h"
#include "program.h"

#ifndef fsm_h
#define fsm_h

#define WELCOME_STATE 0
#define MAIN_STATE 1
#define PROGRAM_STATE 2

#define CHANGE_STRING "CS"
#define NO_CHANGE_STRING "NCS"

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
	int _startState;
	Program program;

	//methods
	void _welcomeState(int event);
	void _mainState(int event);
	void _setState(int event);
	String _runEventMenu(int event, String lineTwoArray[], int arrayLenght, bool showIndex);

	// main
	void _setMain();
	void _runEventMain(int event);
	void _selectMenu();
	
	// welcome
	void _setWelcome();
	void _runEventWelcome(int event);

	// program
	void _setProgram();
	void _runEventProgram(int event);


};


#endif
