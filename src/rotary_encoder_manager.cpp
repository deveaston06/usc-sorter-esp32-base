#include <rotary_encoder_manager.h>

// Variables to store the encoder state
int lastClkState;
unsigned long lastButtonPress = 0;

void setupEncoder() {
  // Set encoder pins as inputs
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  // Use internal pull-up resistor for the switch button
  pinMode(ENCODER_SW, INPUT_PULLUP);

  // Read the initial state of CLK
  lastClkState = digitalRead(ENCODER_CLK);
}

void readEncoderAndScroll() {
  int currentClkState = digitalRead(ENCODER_CLK);

  // Check if the CLK state has changed (rotation occurred)
  if (currentClkState != lastClkState) {

    // If the DT state is different than the CLK state,
    // it means the encoder is rotating Counter-Clockwise (CCW)
    if (digitalRead(ENCODER_DT) != currentClkState) {
      lcdScrollForward();
    }
    // Else, the encoder is rotating Clockwise (CW)
    else {
      lcdScrollBackward();
    }
  }

  // Save the current CLK state for the next loop pass
  lastClkState = currentClkState;

  // Optional: Handle the SW (Switch) button press
  if (digitalRead(ENCODER_SW) == LOW) {
    // Simple software debounce
    if (millis() - lastButtonPress > 300) {
      // Action when button is pressed (e.g., clear or reset position)
      // For now, it just prints a debug message to Serial
      Serial.println("Encoder Button Pressed!");
      lastButtonPress = millis();
    }
  }
}
