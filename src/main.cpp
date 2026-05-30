#include <Arduino.h>
#include <iic_manager.h>
#include <lcd_manager.h>
#include <rotary_encoder_manager.h>
/*
 * ESP32 I2C Master — Slave Scanner with LCD Menu
 *
 * Hardware:
 *   20x4 LCD (parallel 4-bit mode)
 *     VSS → GND
 *     VDD → 5V
 *     VO  → potentiometer wiper (contrast)
 *     RS  → GPIO 12
 *     RW  → GND
 *     EN  → GPIO 13
 *     D4  → GPIO 14
 *     D5  → GPIO 25
 *     D6  → GPIO 26
 *     D7  → GPIO 27
 *     A   → 5V via 220Ω (backlight)
 *     K   → GND (backlight)
 *
 *   KY040 Rotary Encoder
 *     CLK → GPIO 5
 *     DT  → GPIO 18
 *     SW  → GPIO 19
 *     VCC → 3.3V
 *     GND → GND
 *
 *   I2C Bus (to RP2040 slaves)
 *     SDA → GPIO 21
 *     SCL → GPIO 22
 *     2.2kΩ pull-up on SDA to 3.3V
 *     2.2kΩ pull-up on SCL to 3.3V
 *
 * Libraries required:
 *   LiquidCrystal (built-in Arduino)
 *   Wire (built-in Arduino)
 *
 * Behaviour:
 *   - Scans I2C bus on boot and populates slave list
 *   - Rotary encoder scrolls through detected slave addresses
 *   - Button press sends BLINK command (0x01) to selected slave
 *   - Press and hold button (1 second) to rescan I2C bus
 */

void setup() {
  Serial.begin(115200);

  setupLCD();
  setupEncoder();
  setupI2C();

  // initial scan
  delay(200); // let bus settle
  scanI2C();
}

// ─────────────────────────────────────────────────────────────
// LOOP
// ─────────────────────────────────────────────────────────────
void loop() {
  readEncoder();
  handleEncoder();
  handleButton();
}
