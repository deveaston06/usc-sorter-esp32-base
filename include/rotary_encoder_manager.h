#ifndef ROTARY_ENCODER_MANAGER_H
#define ROTARY_ENCODER_MANAGER_H

#include <Arduino.h>
#include <lcd_manager.h>

#define ENC_CLK 19
#define ENC_DT 18
#define ENC_SW 17

#define DEBOUNCE_MS 50
#define HOLD_MS 1000

extern int8_t cursorIndex;  // which slave is highlighted
extern int8_t scrollOffset; // top of visible window (rows 1-3 = 3 visible)

void setupEncoder();
void readEncoder();
void handleEncoder();
void handleButton();

#endif // !ROTARY_ENCODER_MANAGER_H
