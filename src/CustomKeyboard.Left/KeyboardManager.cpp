//
//
//

#include <Keyboard.h>
#include <Mouse.h>
#include "KeyboardButton.h"
#include "KeyboardManager.h"

KeyboardManager::KeyboardManager(LightBar *lightBar) {
  this->ButtonCount = sizeof(this->KeyboardButtons) / sizeof(this->KeyboardButtons[0]);

  this->lightBar = lightBar;
  this->noneButton = KeyboardButton();

  int8_t bounceTime = 5;
  this->KeyboardButtons[0] = KeyboardButton(bounceTime, '`', KeyboardType);
  this->KeyboardButtons[1] = KeyboardButton(bounceTime, KEY_TAB, KeyboardType);
  this->KeyboardButtons[2] = KeyboardButton(bounceTime, KEY_CAPS_LOCK, KeyboardType);
  this->KeyboardButtons[3] = KeyboardButton(bounceTime, KEY_LEFT_SHIFT, KeyboardType);
  this->KeyboardButtons[4] = KeyboardButton(bounceTime, KEY_LEFT_GUI, KeyboardType);

  this->KeyboardButtons[5] = KeyboardButton(bounceTime, '1', KeyboardType);
  this->KeyboardButtons[6] = KeyboardButton(bounceTime, 'q', KeyboardType);
  this->KeyboardButtons[7] = KeyboardButton(bounceTime, 'a', KeyboardType);
  this->KeyboardButtons[8] = KeyboardButton(bounceTime, 'z', KeyboardType);
  this->KeyboardButtons[9] = KeyboardButton(bounceTime, ' ', KeyboardType);

  this->KeyboardButtons[10] = KeyboardButton(bounceTime, '2', KeyboardType);
  this->KeyboardButtons[11] = KeyboardButton(bounceTime, 'w', KeyboardType);
  this->KeyboardButtons[12] = KeyboardButton(bounceTime, 's', KeyboardType);
  this->KeyboardButtons[13] = KeyboardButton(bounceTime, 'x', KeyboardType);
  this->KeyboardButtons[14] = KeyboardButton(bounceTime, ' ', KeyboardType);

  this->KeyboardButtons[15] = KeyboardButton(bounceTime, '3', KeyboardType);
  this->KeyboardButtons[16] = KeyboardButton(bounceTime, 'e', KeyboardType);
  this->KeyboardButtons[17] = KeyboardButton(bounceTime, 'd', KeyboardType);
  this->KeyboardButtons[18] = KeyboardButton(bounceTime, 'c', KeyboardType);
  this->KeyboardButtons[19] = KeyboardButton(bounceTime, KEY_DELETE, KeyboardType);

  this->KeyboardButtons[20] = KeyboardButton(bounceTime, '4', KeyboardType);
  this->KeyboardButtons[21] = KeyboardButton(bounceTime, 'r', KeyboardType);
  this->KeyboardButtons[22] = KeyboardButton(bounceTime, 'f', KeyboardType);
  this->KeyboardButtons[23] = KeyboardButton(bounceTime, 'v', KeyboardType);
  this->KeyboardButtons[24] = KeyboardButton(bounceTime, ' ', KeyboardType);

  this->KeyboardButtons[25] = KeyboardButton(bounceTime, '5', KeyboardType);
  this->KeyboardButtons[26] = KeyboardButton(bounceTime, 't', KeyboardType);
  this->KeyboardButtons[27] = KeyboardButton(bounceTime, 'g', KeyboardType);
  this->KeyboardButtons[28] = KeyboardButton(bounceTime, 'b', KeyboardType);
  this->KeyboardButtons[29] = KeyboardButton(bounceTime, KEY_LEFT_CTRL, KeyboardType);

  this->KeyboardButtons[30] = KeyboardButton(bounceTime, KEY_PRINT_SCREEN, KeyboardType);
  this->KeyboardButtons[31] = KeyboardButton(bounceTime, KEY_MENU, KeyboardType);
  this->KeyboardButtons[32] = KeyboardButton(bounceTime, KEY_LEFT_ALT, KeyboardType);
  this->KeyboardButtons[33] = KeyboardButton(bounceTime, 2, FunctionType);
  this->KeyboardButtons[34] = KeyboardButton(bounceTime / 5, 1, FunctionType);

  this->KeyboardButtons[35] = KeyboardButton(bounceTime, KEY_F1, KeyboardType);
  this->KeyboardButtons[36] = KeyboardButton(bounceTime, KEY_F2, KeyboardType);
  this->KeyboardButtons[37] = KeyboardButton(bounceTime, KEY_F3, KeyboardType);
  this->KeyboardButtons[38] = KeyboardButton(bounceTime, KEY_F4, KeyboardType);
  this->KeyboardButtons[39] = KeyboardButton(bounceTime, KEY_F5, KeyboardType);
  this->KeyboardButtons[40] = KeyboardButton(bounceTime, KEY_F6, KeyboardType);
  this->KeyboardButtons[41] = KeyboardButton(bounceTime, KEY_F7, KeyboardType);
  this->KeyboardButtons[42] = KeyboardButton(bounceTime, KEY_F8, KeyboardType);
  this->KeyboardButtons[43] = KeyboardButton(bounceTime, KEY_F9, KeyboardType);
  this->KeyboardButtons[44] = KeyboardButton(bounceTime, KEY_F10, KeyboardType);
  this->KeyboardButtons[45] = KeyboardButton(bounceTime, KEY_F11, KeyboardType);
  this->KeyboardButtons[46] = KeyboardButton(bounceTime, KEY_F12, KeyboardType);

  this->KeyboardButtons[47] = KeyboardButton(bounceTime, KEY_UP_ARROW, KeyboardType);
  this->KeyboardButtons[48] = KeyboardButton(bounceTime, KEY_DOWN_ARROW, KeyboardType);
  this->KeyboardButtons[49] = KeyboardButton(bounceTime, KEY_LEFT_ARROW, KeyboardType);
  this->KeyboardButtons[50] = KeyboardButton(bounceTime, KEY_RIGHT_ARROW, KeyboardType);

  this->KeyboardButtons[51] = KeyboardButton(bounceTime, KEY_BACKSPACE, KeyboardType);
  this->KeyboardButtons[52] = KeyboardButton(bounceTime, KEY_RETURN, KeyboardType);

  this->KeyboardButtons[53] = KeyboardButton(bounceTime, MOUSE_LEFT, MouseType);
  this->KeyboardButtons[54] = KeyboardButton(bounceTime, MOUSE_RIGHT, MouseType);
  this->KeyboardButtons[55] = KeyboardButton(bounceTime, MOUSE_MIDDLE, MouseType);

  this->KeyboardButtons[56] = KeyboardButton(bounceTime, KEY_ESC, KeyboardType);

  this->KeyboardButtons[57] = KeyboardButton(bounceTime, 'y', FunctionType);
  this->KeyboardButtons[58] = KeyboardButton(bounceTime, 'u', FunctionType);
  this->KeyboardButtons[59] = KeyboardButton(bounceTime, 'h', FunctionType);
  this->KeyboardButtons[60] = KeyboardButton(bounceTime, 'j', FunctionType);
  this->KeyboardButtons[61] = KeyboardButton(bounceTime, 'n', FunctionType);
  this->KeyboardButtons[62] = KeyboardButton(bounceTime, 'm', FunctionType);

  this->KeyboardButtons[63] = KeyboardButton(bounceTime, '<', FunctionType);
  this->KeyboardButtons[64] = KeyboardButton(bounceTime, '>', FunctionType);

  this->KeyboardButtons[65] = KeyboardButton(bounceTime, 'i', FunctionType);
}

void KeyboardManager::OperationState(int8_t rowPin, int8_t columnPin, bool currentState) {
  unsigned long now = millis();

  KeyboardButton *keyboardButton = this->GetLayoutMapping(rowPin, columnPin);

  if (!keyboardButton->IsDebounceTimePassed())
    return;

  if (keyboardButton->CurrentState != currentState) {
    keyboardButton->Execution(currentState, now);

    // 如果使用者按下功能鍵，釋放按鈕資源(LOW(按下中)、HIGH(釋放中))
    if (keyboardButton->KeyType == FunctionType)
      for (int8_t i = 0; i < this->ButtonCount; i++)
        if (this->KeyboardButtons[i].KeyType != FunctionType)
          this->KeyboardButtons[i].Execution(HIGH, now);

    if (keyboardButton->CurrentState == LOW && keyboardButton->KeyType == FunctionType && keyboardButton->KeyValue == 2) {
      this->LayoutIndex++;
      if (this->LayoutIndex >= 3)
        this->LayoutIndex = 0;
    }

    if (keyboardButton->CurrentState == LOW && keyboardButton->KeyType == FunctionType)
      this->lightBar->Update(keyboardButton->KeyValue);
  }
}

KeyboardButton *KeyboardManager::GetLayoutMapping(int8_t rowPin, int8_t columnPin) {
  if (this->KeyboardButtons[34].CurrentState == LOW) {
    KeyboardButton *keyboardButton = this->getExtendLayoutMapping(rowPin, columnPin);
    return keyboardButton;
  } else {
    if (this->LayoutIndex == 1) {
      KeyboardButton *keyboardButton = this->getSecondaryLayoutMapping(rowPin, columnPin);
      return keyboardButton;
    }

    KeyboardButton *keyboardButton = this->getPrimaryLayoutMapping(rowPin, columnPin);
    return keyboardButton;
  }
}

KeyboardButton *KeyboardManager::getPrimaryLayoutMapping(int8_t rowPin, int8_t columnPin) {
  switch (columnPin) {
    case 10:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[0];  // `
          break;
        case 8:
          return &this->KeyboardButtons[1];  // TAB
          break;
        case 9:
          return &this->KeyboardButtons[2];  // CAPS_LOCK
          break;
        case 6:
          return &this->KeyboardButtons[3];  // SHIFT
          break;
        case 5:
          return &this->KeyboardButtons[4];  // GUI
          break;
      }
      break;
    case 16:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[5];  // 1
          break;
        case 8:
          return &this->KeyboardButtons[6];  // Q
          break;
        case 9:
          return &this->KeyboardButtons[7];  // A
          break;
        case 6:
          return &this->KeyboardButtons[8];  // Z
          break;
        case 5:
          return &this->KeyboardButtons[9];  //
          break;
      }
      break;
    case 15:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[10];  // 2
          break;
        case 8:
          return &this->KeyboardButtons[11];  // W
          break;
        case 9:
          return &this->KeyboardButtons[12];  // S
          break;
        case 6:
          return &this->KeyboardButtons[13];  // X
          break;
        case 5:
          return &this->KeyboardButtons[14];  //
          break;
      }
      break;
    case 20:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[15];  // 3
          break;
        case 8:
          return &this->KeyboardButtons[16];  // E
          break;
        case 9:
          return &this->KeyboardButtons[17];  // D
          break;
        case 6:
          return &this->KeyboardButtons[18];  // C
          break;
        case 5:
          return &this->KeyboardButtons[19];  //
          break;
      }
      break;
    case 14:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[20];  // 4
          break;
        case 8:
          return &this->KeyboardButtons[21];  // R
          break;
        case 9:
          return &this->KeyboardButtons[22];  // F
          break;
        case 6:
          return &this->KeyboardButtons[23];  // V
          break;
        case 5:
          return &this->KeyboardButtons[24];  // ' '
          break;
      }
      break;
    case 19:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[25];  // 5
          break;
        case 8:
          return &this->KeyboardButtons[26];  // T
          break;
        case 9:
          return &this->KeyboardButtons[27];  // G
          break;
        case 6:
          return &this->KeyboardButtons[28];  // B
          break;
        case 5:
          return &this->KeyboardButtons[29];  // CTRL
          break;
      }
      break;
    case 18:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[30];  //
          break;
        case 8:
          return &this->KeyboardButtons[31];  //
          break;
        case 6:
          return &this->KeyboardButtons[32];  // ALT
          break;
        case 9:
          return &this->KeyboardButtons[33];  //
          break;
        case 5:
          return &this->KeyboardButtons[34];  // FUNCTION
          break;
      }
      break;
  }
  return &this->noneButton;
}

KeyboardButton *KeyboardManager::getExtendLayoutMapping(int8_t rowPin, int8_t columnPin) {
  switch (columnPin) {
    case 10:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[35];  // F1
          break;
        case 8:
          return &this->KeyboardButtons[1];  // TAB
          break;
        case 9:
          return &this->KeyboardButtons[2];  // CAPS_LOCK
          break;
        case 6:
          return &this->KeyboardButtons[3];  // SHIFT
          break;
        case 5:
          return &this->KeyboardButtons[56];  // ESC
          break;
      }
      break;
    case 16:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[36];  // F2
          break;
        case 8:
          return &this->noneButton;
          break;
        case 9:
          return &this->noneButton;
          break;
        case 6:
          return &this->noneButton;
          break;
        case 5:
          return &this->KeyboardButtons[46];  // F12
          break;
      }
      break;
    case 15:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[37];  // F3
          break;
        case 8:
          return &this->KeyboardButtons[53];  // MOUSE_LEFT
          break;
        case 9:
          return &this->noneButton;
          break;
        case 6:
          return &this->noneButton;
          break;
        case 5:
          return &this->KeyboardButtons[45];  // F11
          break;
      }
      break;
    case 20:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[38];  // F4
          break;
        case 8:
          return &this->KeyboardButtons[55];  // MOUSE_MIDDLE
          break;
        case 9:
          return &this->noneButton;
          break;
        case 6:
          return &this->KeyboardButtons[49];  // KEY LEFT
          break;
        case 5:
          return &this->KeyboardButtons[44];  // F10
          break;
      }
      break;
    case 14:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[39];  // F5
          break;
        case 8:
          return &this->KeyboardButtons[54];  // MOUSE RIGHT
          break;
        case 9:
          return &this->KeyboardButtons[47];  // KEY UP
          break;
        case 6:
          return &this->KeyboardButtons[48];  // KEY DOWN
          break;
        case 5:
          return &this->KeyboardButtons[43];  // F9
          break;
      }
      break;
    case 19:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[40];  // F6
          break;
        case 8:
          return &this->KeyboardButtons[51];  // BACK
          break;
        case 9:
          return &this->KeyboardButtons[52];  // RETURN
          break;
        case 6:
          return &this->KeyboardButtons[50];  // KEY RIGHT
          break;
        case 5:
          return &this->KeyboardButtons[29];  // CTRL
          break;
      }
      break;
    case 18:
      switch (rowPin) {
        case 7:
          return &this->KeyboardButtons[41];  // F7
          break;
        case 8:
          return &this->KeyboardButtons[42];  // F8
          break;
        case 6:
          return &this->KeyboardButtons[32];  // ALT
          break;
        case 9:
          return &this->KeyboardButtons[33];  //
          break;
        case 5:
          return &this->KeyboardButtons[34];  // FUNCTION
          break;
      }
      break;
  }
  return &this->noneButton;
}

KeyboardButton *KeyboardManager::getSecondaryLayoutMapping(int8_t rowPin, int8_t columnPin) {
  switch (columnPin) {
    case 10:
      switch (rowPin) {
        case 7:
          &this->noneButton;
          break;
        case 8:
          &this->noneButton;
          break;
        case 9:
          &this->noneButton;
          break;
        case 6:
          &this->noneButton;
          break;
        case 5:
          &this->noneButton;
          break;
      }
      break;
    case 16:
      switch (rowPin) {
        case 7:
          &this->noneButton;
          break;
        case 8:
          &this->noneButton;
          break;
        case 9:
          &this->noneButton;
          break;
        case 6:
          &this->noneButton;
          break;
        case 5:
          &this->noneButton;
          break;
      }
      break;
    case 15:
      switch (rowPin) {
        case 7:
          &this->noneButton;
          break;
        case 8:
          &this->noneButton;
          break;
        case 9:
          &this->noneButton;
          break;
        case 6:
          return &this->KeyboardButtons[63];  //
          break;
        case 5:
          &this->noneButton;
          break;
      }
      break;
    case 20:
      switch (rowPin) {
        case 7:
          &this->noneButton;
          break;
        case 8:
          return &this->KeyboardButtons[65];  //
          break;
        case 9:
          &this->noneButton;
          break;
        case 6:
          return &this->KeyboardButtons[64];  //
          break;
        case 5:
          &this->noneButton;
          break;
      }
      break;
    case 14:
      switch (rowPin) {
        case 7:
          &this->noneButton;
          break;
        case 8:
          return &this->KeyboardButtons[57];  //
          break;
        case 9:
          return &this->KeyboardButtons[59];  //
          break;
        case 6:
          return &this->KeyboardButtons[61];  //
          break;
        case 5:
          &this->noneButton;
          break;
      }
      break;
    case 19:
      switch (rowPin) {
        case 7:
          &this->noneButton;
          break;
        case 8:
          return &this->KeyboardButtons[58];  //
          break;
        case 9:
          return &this->KeyboardButtons[60];  //
          break;
        case 6:
          return &this->KeyboardButtons[62];  //
          break;
        case 5:
          &this->noneButton;
          break;
      }
      break;
    case 18:
      switch (rowPin) {
        case 7:
          &this->noneButton;
          break;
        case 8:
          &this->noneButton;
          break;
        case 6:
          &this->noneButton;
          break;
        case 9:
          return &this->KeyboardButtons[33];  //
          break;
        case 5:
          return &this->KeyboardButtons[34];  // FUNCTION
          break;
      }
      break;
  }
  return &this->noneButton;
}
