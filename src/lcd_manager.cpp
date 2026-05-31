#include <lcd_manager.h>

// Custom LCD characters
byte arrowUp[8] = {0x04, 0x0E, 0x1F, 0x04, 0x04, 0x04, 0x04, 0x00};
byte arrowDown[8] = {0x04, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04, 0x00};
byte arrowUpDown[8] = {0x04, 0x0E, 0x1F, 0x04, 0x04, 0x1F, 0x0E, 0x04};
byte arrowRight[8] = {0x00, 0x04, 0x06, 0x1F, 0x06, 0x04, 0x00, 0x00};
byte cursor[8] = {0x10, 0x18, 0x1C, 0x1E, 0x1C, 0x18, 0x10, 0x00};

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// ─────────────────────────────────────────────────────────────
// DRAW SCREEN
// ─────────────────────────────────────────────────────────────
void clearRow(uint8_t row) {
  lcd.setCursor(0, row);
  lcd.write("                    ");
  lcd.setCursor(0, row);
}

void drawHeader() {
  clearRow(0);
  lcd.print("I2C Slaves");
  lcd.print("(");
  lcd.print(slaveCount);
  lcd.print(" found)");
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
    clearRow(row + 1);

    if (idx >= slaveCount) {
      continue;
    }

    // cursor arrow
    if (idx == cursorIndex) {
      lcd.write(byte(CHAR_CURSOR));
    } else {
      lcd.print(" ");
    }

    lcd.print(" Slave 0x");
    if (slaveList[idx] < 0x10)
      lcd.print("0");
    lcd.print(slaveList[idx], HEX);
  }

  // scroll indicators on far right of row 0
  lcd.setCursor(19, 0);
  if (scrollOffset > 0 && scrollOffset < slaveCount - 3) {
    lcd.write(byte(CHAR_ARROW_UP_DOWN)); // can scroll both ways
  } else if (scrollOffset > 0) {
    lcd.write(byte(CHAR_ARROW_UP)); // at bottom, can only scroll up
  } else if (slaveCount > 3) {
    lcd.write(byte(CHAR_ARROW_DOWN)); // at top, can scroll down
  } else {
    lcd.print(" "); // 4 or fewer slaves, no scrolling needed
  }
}

void setupLCD() {
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.createChar(CHAR_ARROW_UP, arrowUp);
  lcd.createChar(CHAR_ARROW_DOWN, arrowDown);
  lcd.createChar(CHAR_ARROW_UP_DOWN, arrowUpDown);
  lcd.createChar(CHAR_ARROW_RIGHT, arrowRight);
  lcd.createChar(CHAR_CURSOR, cursor);
  lcd.clear();
}
