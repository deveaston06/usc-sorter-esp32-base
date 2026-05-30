#include <iic_manager.h>

uint8_t slaveCount = 0;
uint8_t slaveList[112]; // max possible I2C slaves

void setupI2C() {
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(I2C_FREQ);
}

// ─────────────────────────────────────────────────────────────
// I2C SCAN
// ─────────────────────────────────────────────────────────────
void scanI2C() {
  slaveCount = 0;
  cursorIndex = 0;
  scrollOffset = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning I2C bus...");

  for (uint8_t addr = SCAN_START; addr <= SCAN_END; addr++) {
    Wire.beginTransmission(addr);
    uint8_t err = Wire.endTransmission();
    if (err == 0) {
      slaveList[slaveCount++] = addr;
    }
    // small yield to prevent WDT on long scans
    if (addr % 16 == 0)
      delay(1);
  }

  drawScreen();
}

// ─────────────────────────────────────────────────────────────
// SEND BLINK COMMAND
// ─────────────────────────────────────────────────────────────
void sendBlink(uint8_t addr) {
  Wire.beginTransmission(addr);
  Wire.write(CMD_BLINK);
  uint8_t err = Wire.endTransmission();

  // brief feedback on LCD row 0
  clearRow(0);
  if (err == 0) {
    lcd.print("CMD sent ");
    lcd.write(char(CHAR_ARROW_RIGHT));
    lcd.print(" 0x");
    if (addr < 0x10)
      lcd.print("0");
    lcd.print(addr, HEX);
    lcd.print("   ");
  } else {
    lcd.print("Send failed (err:");
    lcd.print(err);
    lcd.print(")  ");
  }
  delay(BLINK_FEEDBACK_MS);
  drawHeader();
}
