//
//
//

#include "LightBar.h"

#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>

LightBar::LightBar(Adafruit_NeoPixel *neoPixel) {
  this->neoPixel = neoPixel;
}

void LightBar::Init(KeyboardButton *keyboardButtons, int8_t buttonCount) {
  this->keyboardButtons = keyboardButtons;
  this->buttonCount = buttonCount;

  this->neoPixel->begin();
  this->neoPixel->setBrightness(this->brightness);
  this->neoPixel->show();
}

void LightBar::Update(uint8_t keyValue) {
  int interval = 50;
  if (keyValue == '<') {
    this->brightness = this->brightness - interval;
    this->brightness = this->limitToMinValue(this->brightness, 0);
  } else if (keyValue == '>') {
    this->brightness = this->brightness + interval;
    this->brightness = this->limitToMaxValue(this->brightness, 255);
  } else if (keyValue == 'y') {
    this->redValue = this->redValue - interval;
    this->redValue = this->limitToMinValue(this->redValue, 0);
  } else if (keyValue == 'u') {
    this->redValue = this->redValue + interval;
    this->redValue = this->limitToMaxValue(this->redValue, 255);
  } else if (keyValue == 'h') {
    this->greenValue = this->greenValue - interval;
    this->greenValue = this->limitToMinValue(this->greenValue, 0);
  } else if (keyValue == 'j') {
    this->greenValue = this->greenValue + interval;
    this->greenValue = this->limitToMaxValue(this->greenValue, 255);
  } else if (keyValue == 'n') {
    this->blueValue = this->blueValue - interval;
    this->blueValue = this->limitToMinValue(this->blueValue, 0);
  } else if (keyValue == 'm') {
    this->blueValue = this->blueValue + interval;
    this->blueValue = this->limitToMaxValue(this->blueValue, 255);
  } else if (keyValue == 'i') {
    this->model = this->model + 1;
    if (this->model > 5)
      this->model = 0;
  }
}

int LightBar::limitToMaxValue(int value, int maxValue) {
  if (value >= maxValue)
    return maxValue;
  else
    return value;
}

int LightBar::limitToMinValue(int value, int minValue) {
  if (value <= minValue)
    return minValue;
  else
    return value;
}

void LightBar::Exec(uint8_t layoutIndex) {
  unsigned long currentMillis = millis();

  if (layoutIndex == 2)
    this->neoPixel->setBrightness(0);
  else
    this->neoPixel->setBrightness(this->brightness);

  if (this->model == 0 || this->model == 1)
    for (int i = 0; i < neoPixel->numPixels(); i++)
      this->neoPixel->setPixelColor(i, this->neoPixel->Color(this->redValue, this->greenValue, this->blueValue));

  if (this->model == 1) {
    if (currentMillis - this->previousFadeMillis >= 100) {
      this->previousFadeMillis = currentMillis;
      this->brightness = this->brightness + this->fadeInterval;
      if (this->brightness <= 5 || this->brightness >= 250) {
        this->fadeInterval = -this->fadeInterval;
      }
    }
  } else if (this->model == 2) {
    if (currentMillis - this->previousWaveMillis >= 100) {
      this->previousWaveMillis = currentMillis;
      this->waveIndex = this->waveIndex + this->waveInterval;
      if (this->waveIndex <= 0 || this->waveIndex >= 5)
        this->waveInterval = -this->waveInterval;

      for (int i = 0; i < neoPixel->numPixels(); i++) {
        int distance = abs(this->waveIndex - i);

        if (distance >= 0 && distance <= 5)
          this->neoPixel->setPixelColor(i, this->neoPixel->Color(this->redValue - (distance * 30), this->greenValue - (distance * 30), this->blueValue - (distance * 30)));
        else
          this->neoPixel->setPixelColor(i, this->neoPixel->Color(0, 0, 0));
      }
    }
  } else if (this->model == 3) {
    if (currentMillis - this->previousWaveMillis >= 250) {
      this->previousWaveMillis = currentMillis;
      this->waveIndex = this->waveIndex + this->waveInterval;
      if (this->waveIndex <= 0 || this->waveIndex >= 5)
        this->waveInterval = -this->waveInterval;

      for (int i = 0; i < neoPixel->numPixels(); i++) {
        int distance = abs(this->waveIndex - i);

        if (this->waveInterval > 0) {
          if (i <= this->waveIndex) {
            this->neoPixel->setPixelColor(i, this->neoPixel->Color(this->redValue - (distance * 30), this->greenValue - (distance * 30), this->blueValue - (distance * 30)));
          } else {
            this->neoPixel->setPixelColor(i, this->neoPixel->Color(0, 0, 0));
          }
        } else {
          if (i >= this->waveIndex) {
            this->neoPixel->setPixelColor(i, this->neoPixel->Color(this->redValue - (distance * 30), this->greenValue - (distance * 30), this->blueValue - (distance * 30)));
          } else {
            this->neoPixel->setPixelColor(i, this->neoPixel->Color(0, 0, 0));
          }
        }
      }
    }
  } else if (this->model == 4) {
    if (currentMillis - this->previousRainbowMillis >= 50) {
      this->previousRainbowMillis = currentMillis;
      this->rainbowOffset++;

      int segments = 3;
      int segmentLength = neoPixel->numPixels() / segments;

      for (int i = 0; i < neoPixel->numPixels(); i++) {
        int segment = i / segmentLength;
        int colorPos = (i + this->rainbowOffset + segment * 85) % 255;

        neoPixel->setPixelColor(i, this->wheel(colorPos));
      }
    }
  } else if (this->model == 5) {
    for (int i = 0; i < neoPixel->numPixels(); i++)
      this->neoPixel->setPixelColor(i, this->neoPixel->Color(0, 0, 0));

    for (int i = 0; i < this->buttonCount; i++) {
      KeyboardButton *keyboardButton = &this->keyboardButtons[i];
      if (keyboardButton->CurrentState == LOW) {
        if (keyboardButton->KeyValue == KEY_RIGHT_CTRL) {
          this->neoPixel->setPixelColor(5, this->neoPixel->Color(this->redValue, this->greenValue, this->blueValue));
          this->neoPixel->setPixelColor(4, this->neoPixel->Color(this->redValue, this->greenValue, this->blueValue));
        } else if (keyboardButton->KeyValue == 'k') {
          this->neoPixel->setPixelColor(4, this->neoPixel->Color(this->redValue, this->greenValue, this->blueValue));
          this->neoPixel->setPixelColor(3, this->neoPixel->Color(this->redValue, this->greenValue, this->blueValue));
        } else if (keyboardButton->KeyValue == 'l') {
          this->neoPixel->setPixelColor(3, this->neoPixel->Color(this->redValue, this->greenValue, this->blueValue));
          this->neoPixel->setPixelColor(2, this->neoPixel->Color(this->redValue, this->greenValue, this->blueValue));
        } else if (keyboardButton->KeyValue == ';') {
          this->neoPixel->setPixelColor(2, this->neoPixel->Color(this->redValue, this->greenValue, this->blueValue));
          this->neoPixel->setPixelColor(1, this->neoPixel->Color(this->redValue, this->greenValue, this->blueValue));
        } else if (keyboardButton->KeyValue == ']') {
          this->neoPixel->setPixelColor(1, this->neoPixel->Color(this->redValue, this->greenValue, this->blueValue));
          this->neoPixel->setPixelColor(0, this->neoPixel->Color(this->redValue, this->greenValue, this->blueValue));
        }
      }
    }
  }

  this->neoPixel->show();
}

uint32_t LightBar::wheel(byte wheelPos) {
  wheelPos = 255 - wheelPos;
  if (wheelPos < 85) {
    return neoPixel->Color(255 - wheelPos * 3, 0, wheelPos * 3);
  } else if (wheelPos < 170) {
    wheelPos -= 85;
    return neoPixel->Color(0, wheelPos * 3, 255 - wheelPos * 3);
  } else {
    wheelPos -= 170;
    return neoPixel->Color(wheelPos * 3, 255 - wheelPos * 3, 0);
  }
}