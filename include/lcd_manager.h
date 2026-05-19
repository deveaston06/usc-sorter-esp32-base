#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LiquidMenu.h>
#include <rotary_encoder_manager.h>

void setupLCD();
void processSerialEditAndEncoder();
void lcdScrollForward();
void lcdScrollBackward();

#endif // !LCD_MANAGER_H
