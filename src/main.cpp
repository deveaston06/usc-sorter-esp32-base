#include <Arduino.h>
#include <iic_manager.h>
#include <lcd_manager.h>
#include <rotary_encoder_manager.h>

void setup() {
  Serial.begin(115200);
  // setupI2C();
  // scanForI2CDevices();
  setupLCD();
  setupEncoder();
}

void loop() {
  // sendMessageFromSerial(PERIPHERAL_ADDRESS);
  // delay(5000);

  processSerialEditAndEncoder();
  delay(1);
}
