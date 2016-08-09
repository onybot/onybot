#include "Arduino.h"
#include <LiquidCrystal.h>

#include "constants.h"
#include "utils.h"
#include "event.h"
#include "fsm.h"


//////////////////////////////////
// GLOBALS
//////////////////////////////////

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Event event;
Fsm fsm;

void setup() {
	//init serial monitor
	Serial.begin(9600);
	Serial.println("Setup fun");

	//init lcd
	lcd.begin(LCD_CHARS, LCD_LINES);        
	pinMode(LCD_CTRL_LIGHT_PIN, OUTPUT);
	analogWrite(LCD_CTRL_LIGHT_PIN, DEFAULT_LCD_LIGHT);

	//init fsm
	fsm.init();
	lcdPrintLine(lcd, 0, fsm.firstLine);
	lcdPrintLine(lcd, 1, fsm.secondLine);
}


void loop() {
	int light;
	if(fsm.run_event(event.getEvent())){
		lcdPrintLine(lcd, 0, fsm.firstLine);
		lcdPrintLine(lcd, 1, fsm.secondLine);
	}
	if (fsm.automaticLight == true && LCD_AUTOMATIC_LIGHT == true){
		light = event.getLightIntensity();
		analogWrite(LCD_CTRL_LIGHT_PIN, light);
	}
	delay(LOOP_WAITING);
}