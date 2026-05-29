#include <lcd_manager.h>

// Custom LCD characters
byte arrowUp[8] = {0x04, 0x0E, 0x1F, 0x04, 0x04, 0x04, 0x04, 0x00};
byte arrowDown[8] = {0x04, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04, 0x00};
byte cursor[8] = {0x10, 0x18, 0x1C, 0x1E, 0x1C, 0x18, 0x10, 0x00};

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// ─────────────────────────────────────────────────────────────
// DRAW SCREEN
// ─────────────────────────────────────────────────────────────
void drawHeader() {
  lcd.setCursor(0, 0);
  lcd.print("I2C Slaves ");
  lcd.print("(");
  lcd.print(slaveCount);
  lcd.print(" found)     ");
}

void drawScreen() {
  lcd.clear();
  drawHeader();

  if (slaveCount == 0) {
    lcd.setCursor(0, 1);
    lcd.print("  No slaves found   ");
    lcd.setCursor(0, 2);
    lcd.print("  Hold BTN rescan   ");
    return;
  }

  // rows 1-3 show 3 slaves at a time
  for (uint8_t row = 0; row < 3; row++) {
    int idx = scrollOffset + row;
    lcd.setCursor(0, row + 1);

    if (idx >= slaveCount) {
      lcd.print("                    ");
      continue;
    }

    // cursor arrow
    if (idx == cursorIndex) {
      lcd.write(byte(2)); // cursor character
    } else {
      lcd.print(" ");
    }

    lcd.print(" Slave 0x");
    if (slaveList[idx] < 0x10)
      lcd.print("0");
    lcd.print(slaveList[idx], HEX);

    // pad remaining columns
    lcd.print("            ");
  }

  // scroll indicators on far right of row 0
  lcd.setCursor(19, 0);
  if (scrollOffset > 0) {
    lcd.write(byte(0)); // up arrow
  } else {
    lcd.print(" ");
  }
}

void setupLCD() {
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.createChar(0, arrowUp);
  lcd.createChar(1, arrowDown);
  lcd.createChar(2, cursor);
  lcd.clear();
}
