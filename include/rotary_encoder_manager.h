#ifndef ROTARY_ENCODER_MANAGER_H
#define ROTARY_ENCODER_MANAGER_H

#include <Arduino.h>
#include <lcd_manager.h>

#define ENCODER_CLK 5
#define ENCODER_DT 18
#define ENCODER_SW 19

void setupEncoder();
void readEncoderAndScroll();

#endif // !ROTARY_ENCODER_MANAGER_H
