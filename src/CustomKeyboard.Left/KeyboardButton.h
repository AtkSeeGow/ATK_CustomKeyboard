// KeyboardButton.h

#ifndef _KEYBOARDBUTTON_h
#define _KEYBOARDBUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

enum KeyType {
  None = 1,
  KeyboardType,
  MouseType,
  FunctionType
};

class KeyboardButton {
  public:
    KeyboardButton();
    KeyboardButton(unsigned long bounceTime, uint8_t keyValue, uint8_t keyType);

    KeyType KeyType;
    uint8_t KeyValue;
    bool CurrentState;
    
    bool IsDebounceTimePassed();

    void Execution(bool currentState, unsigned long lastChangeStateTime);
    
  private:
    void operationPress();
    void operationRelease();



    unsigned long bounceTime;
    unsigned long lastChangeStateTime;
};

#endif
