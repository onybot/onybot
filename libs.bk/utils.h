#include "Arduino.h"
#ifndef utils_h
#define utils_h
#include <LiquidCrystal.h>

void clearLine(LiquidCrystal lcd, int line);
void lcdPrintLine(LiquidCrystal lcd, int line, String s);
void log(String s);
#endif