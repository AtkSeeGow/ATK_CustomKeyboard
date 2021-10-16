// KeyboardManager.h

#ifndef _KEYBOARDMANAGER_h
#define _KEYBOARDMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "KeyboardButton.h"

#include <LiquidCrystal_I2C.h>

class KeyboardManager {
  public:
    KeyboardManager(LiquidCrystal_I2C *liquidCrystalI2C);

    void OperationState(int8_t rowPin, int8_t columnPin, bool currentState);
    void Execution();
    void DisplayMappingModeName();

    KeyboardButton *GetMapping(int8_t rowPin, int8_t columnPin);
  private:
    LiquidCrystal_I2C *liquidCrystalI2C;

    KeyboardButton *getBasicMapping(int8_t rowPin, int8_t columnPin);
    KeyboardButton *getExtendMapping(int8_t rowPin, int8_t columnPin);

    KeyboardButton keyboardButtons[53];
    KeyboardButton noneButton;
};

#endif
