#include <lcd_manager.h>

const int rs = 12, en = 13, d4 = 14, d5 = 25, d6 = 26, d7 = 27;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

LiquidScreen screen;
LiquidMenu menu(lcd);

const int MAX_DYNAMIC_LINES = 4;
char lineBuffers[MAX_DYNAMIC_LINES][21];
LiquidLine *lines[MAX_DYNAMIC_LINES];

void blankFunction() { return; }

void addLineText(int index, const char *text) {
  if (index >= 0 && index < MAX_DYNAMIC_LINES) {
    strncpy(lineBuffers[index], text, 19);
    lineBuffers[index][19] = '\0';
    menu.update();
  }
}

void deleteLineText(int index) {
  if (index >= 0 && index < MAX_DYNAMIC_LINES) {
    strcpy(lineBuffers[index], "                   ");
    menu.update();
  }
}

void setupLCD() {
  lcd.begin(20, 4);
  menu.init();

  for (int i = 0; i < MAX_DYNAMIC_LINES; i++) {
    strcpy(lineBuffers[i], "                   ");

    lines[i] = new LiquidLine(1, i, lineBuffers[i]);

    lines[i]->set_focusPosition(Position::LEFT);
    lines[i]->attach_function(1, blankFunction);

    screen.add_line(*lines[i]);
  }

  menu.add_screen(screen);
  menu.update();
}

void lcdScrollBackward() {
  menu.switch_focus(false);
  menu.update();
}

void lcdScrollForward() {
  menu.switch_focus(true);
  menu.update();
}

bool isSerialInputActive = false;
int currentEditIndex = -1;
int charIndex = 0;

void processSerialInput() {
  if (!isSerialInputActive) {
    if (digitalRead(ENCODER_SW) == LOW) {
      currentEditIndex = menu.get_focusedLine();
      isSerialInputActive = true;
      charIndex = 0;
      memset(lineBuffers[currentEditIndex], ' ', 19);
      lineBuffers[currentEditIndex][19] = '\0';
      Serial.println("Edit mode active. Enter text:");
    }
    return;
  }

  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      lineBuffers[currentEditIndex][charIndex] = '\0';
      isSerialInputActive = false;
      menu.update();
      Serial.println("Line updated.");
    } else if (charIndex < 19) {
      lineBuffers[currentEditIndex][charIndex] = c;
      charIndex++;
      lineBuffers[currentEditIndex][charIndex] = '\0';
      menu.update();
    }
  }
}

void processSerialEditAndEncoder() {
  processSerialInput();

  if (!isSerialInputActive) {
    readEncoderAndScroll();
  }
}
