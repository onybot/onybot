#include "Arduino.h"
#include "program.h"

#ifndef fsm_h
#define fsm_h

#define WELCOME_STATE 0
#define MAIN_STATE 1
#define PROGRAM_STATE 2
#define VIEW_STATE 3
#define DELETE_STATE 4
#define VERSION_STATE 5
#define RUN_STATE 6

#define INITIAL_STATE WELCOME_STATE



class Fsm {

	public:
	//methods
	void init();
	bool runEvent(int event);

	//attributes
	String firstLine;
	String secondLine;
	bool automaticLight;

	private:


	//Attributes
	int _currentState;
	int _menuIndex;
	int _menuViewIndex;
	bool _changedLine;
	int _startState;
	Program program;
	bool _wait;
	//methods
	void _welcomeState(int event);
	void _mainState(int event);
	void _setState(int event);

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

	// view
	void _setView();
	void _runEventView(int event);	

	// run
	void _setRun();
	void _runEventRun(int event);

	// delete
	void _setDelete();
	void _runEventDelete(int event);

	// version
	void _setVersion();
	void _runEventVersion(int event);

};


#endif
