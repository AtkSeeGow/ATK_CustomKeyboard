#include <Keyboard.h>

int8_t rowPins[] = { 5, 6, 7, 8, 9 };
int8_t columnPins[] = { 10, 14, 15, 16, 18, 19, 20 };

void setup() {
  Serial.begin(9600);

  for (int8_t pin : rowPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  for (int8_t pin : columnPins) {
    pinMode(pin, INPUT_PULLUP);
  }
}

unsigned long LastChangeStateTime;
void loop() {
  for (int8_t rowPin : rowPins) {
    digitalWrite(rowPin, LOW);

    for (int8_t columnPin : columnPins) {
      bool currentState = digitalRead(columnPin);
      if (currentState == LOW) {

        unsigned long now = millis();
        if (now - LastChangeStateTime > 1000) {
          Serial.print(rowPin);
          Serial.print(",");
          Serial.print(columnPin);
          Serial.print(",");
          Serial.print(now);
          Serial.print(",");
          Serial.println(LastChangeStateTime);
          Keyboard.press(0x20);
          Keyboard.release(0x20);
          LastChangeStateTime = now;
        }
      }
    }

    digitalWrite(rowPin, HIGH);
  }
}
