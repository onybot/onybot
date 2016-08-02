#include "Arduino.h"
#include "event.h"

Event::Event(){
  _lastChange=0;
  _lastButton=BTN_NONE;
}

int Event::_readButton(){
   int analog_key  = analogRead(0);
   if (analog_key < BTN_RIGHT_THRESHOLD){
     return BTN_RIGHT; 
   }
   if (analog_key < BTN_UP_THRESHOLD){
    return BTN_UP; 
   }
   if (analog_key < BTN_DOWN_THRESHOLD){
     return BTN_DOWN; 
   }
   if (analog_key < BTN_LEFT_THRESHOLD){
    return  BTN_LEFT; 
   }
   if (analog_key < BTN_SELECT_THRESHOLD){
     return BTN_SELECT;  
   }
  return BTN_NONE;
  
}

// read the buttons
int Event::getEvent()
{
   int return_btn;
   int pressed = _readButton();
   int now = millis();
   return_btn = pressed;        
   if (pressed == _lastButton && pressed != BTN_NONE && now - _lastChange < PRESS_STEP)
   {     
     return_btn = BTN_NONE; 
   } else {
     _lastChange = now;
   }     
   _lastButton = pressed;
   if (return_btn != BTN_NONE)
   {
     Serial.println("btn pressed: " + String(pressed, DEC));
   }
   return return_btn;
}   
