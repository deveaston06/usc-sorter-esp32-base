#include <rotary_encoder_manager.h>

int8_t cursorIndex = 0;  // which slave is highlighted
int8_t scrollOffset = 0; // top of visible window (rows 1-3 = 3 visible)

// encoder state
volatile int encDelta = 0;
int lastCLK = HIGH;

// button state
bool lastBtnState = HIGH;
uint32_t btnPressTime = 0;
bool btnHoldFired = false;

void setupEncoder() {
  pinMode(ENC_CLK, INPUT_PULLUP);
  pinMode(ENC_DT, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);
  lastCLK = digitalRead(ENC_CLK);
}

void readEncoder() {
  int clkState = digitalRead(ENC_CLK);
  if (clkState != lastCLK && clkState == LOW) {
    if (digitalRead(ENC_DT) != clkState) {
      encDelta++;
    } else {
      encDelta--;
    }
  }
  lastCLK = clkState;
}

void handleEncoder() {
  if (encDelta == 0)
    return;

  int move = encDelta;
  encDelta = 0;

  if (slaveCount == 0)
    return;

  cursorIndex += move;

  // clamp
  if (cursorIndex < 0)
    cursorIndex = 0;
  if (cursorIndex >= slaveCount)
    cursorIndex = slaveCount - 1;

  // adjust scroll window (3 visible rows)
  if (cursorIndex < scrollOffset) {
    scrollOffset = cursorIndex;
  }
  if (cursorIndex >= scrollOffset + 3) {
    scrollOffset = cursorIndex - 2;
  }

  drawScreen();
}

void handleButton() {
  bool btnState = digitalRead(ENC_SW);

  // button pressed (active LOW)
  if (btnState == LOW && lastBtnState == HIGH) {
    btnPressTime = millis();
    btnHoldFired = false;
    delay(DEBOUNCE_MS);
  }

  // button held
  if (btnState == LOW && !btnHoldFired) {
    if (millis() - btnPressTime >= HOLD_MS) {
      btnHoldFired = true;
      scanI2C();
    }
  }

  // button released
  if (btnState == HIGH && lastBtnState == LOW) {
    if (!btnHoldFired && slaveCount > 0) {
      sendBlink(slaveList[cursorIndex]);
    }
    delay(DEBOUNCE_MS);
  }

  lastBtnState = btnState;
}
