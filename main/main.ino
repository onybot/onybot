#include "Arduino.h"
#include <LiquidCrystal.h>

#include "constants.h"
#include "utils.h"

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);



void setup() {
	//init serial monitor
	Serial.begin(9600);
	Serial.println("Setup fun");

//init lcd
	lcd.begin(LCD_CHARS, LCD_LINES);        
	pinMode(LCD_CTRL_LIGHT, OUTPUT);
	analogWrite(LCD_CTRL_LIGHT, DEFAULT_LCD_LIGHT);
	lcd.setCursor(0,0);
	lcdPrintLine(lcd, 0, WELCOME_STRING_1);
	lcdPrintLine(lcd, 1, WELCOME_STRING_2);
}


void loop() {

}