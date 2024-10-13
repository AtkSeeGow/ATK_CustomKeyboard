//
//
//

#include <Mouse.h>
#include <Keyboard.h>
#include "KeyboardButton.h"

KeyboardButton::KeyboardButton() {
  this->KeyValue = 0;
  this->KeyType = None;
}

KeyboardButton::KeyboardButton(unsigned long bounceTime, uint8_t keyValue, uint8_t keyType) {
  this->KeyValue = keyValue;
  this->KeyType = keyType;
  this->CurrentState = HIGH;

  this->bounceTime = bounceTime;
  this->lastChangeStateTime = 0;
}

void KeyboardButton::Exec(bool currentState, unsigned long lastChangeStateTime) {
  this->CurrentState = currentState;

  this->lastChangeStateTime = lastChangeStateTime;

  this->operationPress();
  this->operationRelease();
}

bool KeyboardButton::IsDebounceTimePassed() {
  unsigned long now = millis();
  return now - this->lastChangeStateTime > this->bounceTime;
}

void KeyboardButton::operationPress() {
  if (this->CurrentState == LOW) {
    if (this->KeyType == KeyboardType)
      Keyboard.press(this->KeyValue);
    else if (this->KeyType == MouseType)
      Mouse.press(this->KeyValue);
  }
}

void KeyboardButton::operationRelease() {
  if (this->CurrentState == HIGH) {
    if (this->KeyType == KeyboardType)
      Keyboard.release(this->KeyValue);
    else if (this->KeyType == MouseType)
      Mouse.release(this->KeyValue);
  }
}
