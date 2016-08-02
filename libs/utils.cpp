#include "Arduino.h"
#include "utils.h"
#include <LiquidCrystal.h>
#include "constants.h"



void clearLine(LiquidCrystal lcd, int line){
  lcd.setCursor(0,line);
  for(int i=0; i<LCD_CHARS; i++){
    lcd.print(" ");
  }
}
void lcdPrintLine(LiquidCrystal lcd, int line, String s){
	clearLine(lcd,line);	
	lcd.setCursor(0, line);
	lcd.print(s);
}

void log(String s){
	Serial.println(s);
}