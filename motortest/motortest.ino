#include "Arduino.h"
#include <LiquidCrystal.h>
#include "motortest.h"
#include "utils.h"
#include "robot.h"


//////////////////////////////////
// GLOBALS
//////////////////////////////////

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int state = 0;

void setup() {
	//init serial monitor
	Serial.begin(9600);
	Serial.println("Setup fun");
	
	//MOTORS
	pinMode(MOTOR_RIGHT_1, OUTPUT);   // sets the pin as output
	pinMode(MOTOR_RIGHT_2, OUTPUT);   // sets the pin as output
	pinMode(MOTOR_LEFT_1, OUTPUT);   // sets the pin as output
	pinMode(MOTOR_LEFT_2, OUTPUT);   // sets the pin as output




	//init lcd
	lcd.begin(LCD_CHARS, LCD_LINES);        
	pinMode(LCD_CTRL_LIGHT_PIN, OUTPUT);
	analogWrite(LCD_CTRL_LIGHT_PIN, DEFAULT_LCD_LIGHT);

	lcdPrintLine(lcd, 0, "LCD");
	lcdPrintLine(lcd, 1, "TEST");
}


void loop() {

	Serial.println("loop");

	switch (state) {
		case 0:
			digitalWrite(MOTOR_RIGHT_1, LOW);
			digitalWrite(MOTOR_RIGHT_2, HIGH);
			digitalWrite(MOTOR_LEFT_1, LOW);
			digitalWrite(MOTOR_LEFT_2, HIGH);
			break;
		case 1:
			digitalWrite(MOTOR_RIGHT_1, LOW);
			digitalWrite(MOTOR_RIGHT_2, LOW);
			digitalWrite(MOTOR_LEFT_1, LOW);
			digitalWrite(MOTOR_LEFT_2, LOW);
			break;

		case 2:
			digitalWrite(MOTOR_RIGHT_1, HIGH);
			digitalWrite(MOTOR_RIGHT_2, LOW);
			digitalWrite(MOTOR_LEFT_1, HIGH);
			digitalWrite(MOTOR_LEFT_2, LOW);
			break;

		case 3:
			digitalWrite(MOTOR_RIGHT_1, LOW);
			digitalWrite(MOTOR_RIGHT_2, LOW);
			digitalWrite(MOTOR_LEFT_1, LOW);
			digitalWrite(MOTOR_LEFT_2, LOW);
			break;
		default:
			break;
		}
	state ++;
	state = state % 4;

	delay(LOOP_WAITING);
}

