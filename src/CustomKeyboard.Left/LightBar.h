// LightBar.h

#ifndef _LIGHTBAR_h
#define _LIGHTBAR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_NeoPixel.h>
#include "KeyboardButton.h"


class LightBar {
public:
  LightBar(Adafruit_NeoPixel *neoPixel);
  void Init(KeyboardButton *keyboardButtons, int8_t buttonCount);
  void Update(uint8_t keyValue);
  void Exec(uint8_t layoutIndex);


private:
  uint8_t model = 0;

  int8_t buttonCount = 0;
  KeyboardButton *keyboardButtons;

  int brightness = 50;
  int redValue = 200;
  int greenValue = 200;
  int blueValue = 200;

  int fadeInterval = 5;
  unsigned long previousFadeMillis = 0;

  int waveIndex = 0;
  int waveInterval = 1;
  unsigned long previousWaveMillis = 0;

  int rainbowOffset = 0;
  unsigned long previousRainbowMillis = 0;

  Adafruit_NeoPixel *neoPixel;

  int limitToMinValue(int value, int minValue);
  int limitToMaxValue(int value, int maxValue);
  uint32_t wheel(byte wheelPos);
};

#endif
