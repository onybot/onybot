#include "Arduino.h"
#include "event.h"
#include "menu.h"
#include "constants.h"


Menu::Menu(){}


void Menu::runEvent(int event, int menuIndex, String lineTwoArray[], int arrayLenght, bool looping){
	int previous;

	previous = menuIndex;
	
	selected = false;
	back = false;

	// first time
	if (menuIndex == -1){
		menuIndex = 0;
	} else {
		if (event == BTN_UP){
			menuIndex = menuIndex - 1;
			
		} else if (event == BTN_DOWN){
			menuIndex = menuIndex + 1;
			
		} else if (event == BTN_SELECT || event == BTN_RIGHT){
			// change state
			selected = true;
			index = menuIndex;
			return;
		} else if (event == BTN_LEFT){
			// change state
			back = true;
			index = menuIndex;
			return;
		}
		if (menuIndex < 0 ){
			if (looping == true){
				menuIndex = arrayLenght - 1;
			} else {
				menuIndex = 0;
			}
		}
		if (menuIndex > arrayLenght - 1){
			if (looping == true){
				menuIndex = 0;
			} else {
				menuIndex = arrayLenght - 1;
			}
		}
		menuIndex = menuIndex % arrayLenght;
	}
	if (menuIndex != previous){
		index = menuIndex;
	} else {
		index = -1;
	}
	Serial.println("index");
	Serial.println(index);
}

