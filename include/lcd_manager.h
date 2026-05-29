#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <iic_manager.h>
#include <rotary_encoder_manager.h>

#define LCD_RS 12
#define LCD_EN 13
#define LCD_D4 14
#define LCD_D5 25
#define LCD_D6 26
#define LCD_D7 27
#define LCD_COLS 20
#define LCD_ROWS 4

extern LiquidCrystal lcd;

void setupLCD();
void drawScreen();
void drawHeader();

#endif // !LCD_MANAGER_H
