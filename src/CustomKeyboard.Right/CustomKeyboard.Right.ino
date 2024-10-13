#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>

#include "KeyboardButton.h"
#include "KeyboardManager.h"
#include "LightBar.h"

LiquidCrystal_I2C lcd(0x3F, 16, 2);
Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(6, A3, NEO_GRB + NEO_KHZ800);
LightBar lightBar = LightBar(&neoPixel);
KeyboardManager keyboardManager = KeyboardManager(&lightBar);

int8_t rowPins[] = { 10, 14, 15, 16, A0 };
int8_t columnPins[] = { 3, 4, 5, 6, 7, 8, 9 };

void setup() {
  Serial.begin(9600);

  lightBar.Init(keyboardManager.KeyboardButtons, keyboardManager.ButtonCount);

  for (int8_t pin : rowPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  for (int8_t pin : columnPins) {
    pinMode(pin, INPUT_PULLUP);
  }

  lcd.init();
  lcd.backlight();
}

void loop() {
  for (int8_t rowPin : rowPins) {
    digitalWrite(rowPin, LOW);

    for (int8_t columnPin : columnPins) {
      bool currentState = digitalRead(columnPin);
      keyboardManager.OperationState(rowPin, columnPin, currentState);
    }

    digitalWrite(rowPin, HIGH);
  }

  lightBar.Exec(keyboardManager.LayoutIndex);

  if (keyboardManager.LayoutIndex == 2)
    lcd.setBacklight(0);
  else
    lcd.setBacklight(128);

  if (keyboardManager.LayoutIndex == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Primary Layout");
  } else if (keyboardManager.LayoutIndex == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Secondary Layout  ");
  } else {
    lcd.clear();
  }
}
