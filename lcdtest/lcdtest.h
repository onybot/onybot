
#ifndef lcdtest_h
#define lcdtest_h

#define LOOP_WAITING 500


//COMMON
#define MAX_ANALOG_WRITE 255


//LCD

#define LCD_CHARS 16
#define LCD_LINES 2
#define LCD_CTRL_LIGHT_PIN 10
#define LCD_LIGHT_MIN 0
#define LCD_LIGHT_MAX MAX_ANALOG_WRITE
#define DEFAULT_LCD_LIGHT LCD_LIGHT_MAX/30
#define LCD_LIGHT_TIME 2000
#define LCD_AUTOMATIC_LIGHT false

#endif