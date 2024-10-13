// KeyboardManager.h

#ifndef _KEYBOARDMANAGER_h
#define _KEYBOARDMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "LightBar.h"
#include "KeyboardButton.h"

class KeyboardManager {
  public:
    KeyboardManager(LightBar *lightBar);

    void OperationState(int8_t rowPin, int8_t columnPin, bool currentState);

    int8_t LayoutIndex = 0;
    int8_t ButtonCount = 0;
    KeyboardButton KeyboardButtons[66];
    KeyboardButton *GetLayoutMapping(int8_t rowPin, int8_t columnPin);
  private:
    KeyboardButton *getPrimaryLayoutMapping(int8_t rowPin, int8_t columnPin);
    KeyboardButton *getSecondaryLayoutMapping(int8_t rowPin, int8_t columnPin);
    KeyboardButton *getExtendLayoutMapping(int8_t rowPin, int8_t columnPin);
    
    KeyboardButton noneButton;

    LightBar *lightBar;
};

#endif
