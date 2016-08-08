#include "Arduino.h"
#include "program.h"



Program::Program(){
	int i;
	i = 0;
}


bool Program::addCommand(String command){
	int i;
	i = 0;
	Serial.println(command);
	return true;


}