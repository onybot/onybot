#include "Arduino.h"
#include <LiquidCrystal.h>
#include "motortest.h"
#include "utils.h"
#include "motors.h"
#include "robot.h"


//////////////////////////////////
// GLOBALS
//////////////////////////////////

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

Motors motors;

void setup() {
	//init serial monitor
	Serial.begin(9600);
	Serial.println("Setup fun");
	
	motors.init();
	//init lcd
	lcd.begin(LCD_CHARS, LCD_LINES);        
	pinMode(LCD_CTRL_LIGHT_PIN, OUTPUT);
	analogWrite(LCD_CTRL_LIGHT_PIN, DEFAULT_LCD_LIGHT);

	lcdPrintLine(lcd, 0, "MOTORS");
	lcdPrintLine(lcd, 1, "TEST");
}


void loop() {
	Serial.println("loop");
	motors.setShortTurnLeft();
	motors.setFordward();
	motors.setBack();
	motors.setShortTurnLeft();
	motors.setLongTurnLeft();
	motors.setShortTurnRight();
	motors.setLongTurnRight();
	motors.setStop();
	delay(LOOP_WAITING);
}


