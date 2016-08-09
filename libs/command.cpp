#include "Arduino.h"
#include "command.h"
#include "constants.h"


Command::Command(){
	empty = false;
}

void Command::run(){
	delay(COMMAND_TEST_DELAY);
}