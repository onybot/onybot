#include "Arduino.h"

#ifndef event_h
#define event_h




// define some values used by the panel and buttons
#define BTN_NONE   -1
#define BTN_RIGHT   0
#define BTN_UP      1
#define BTN_DOWN    2
#define BTN_LEFT    3
#define BTN_SELECT  4
#define BTN_SLEEP   5

#define PRESS_STEP 100//millisecs


#define BTN_RIGHT_THRESHOLD 50 
#define BTN_UP_THRESHOLD 250
#define BTN_DOWN_THRESHOLD  450
#define BTN_LEFT_THRESHOLD 650
#define BTN_SELECT_THRESHOLD 850

class Event
{
  public:
  //methods
   Event();
   int getEvent();
  //attributes
  
  private:
    //Methods
    int _readButton();
    //Attributes
    int _lastChange;
    int _lastButton;


};

#endif