#ifndef IIC_MANAGER_H
#define IIC_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include <lcd_manager.h>

#define I2C_SDA 21
#define I2C_SCL 22
#define ALERT 23
#define I2C_FREQ 100000
#define CMD_BLINK 0x01
#define SCAN_START 0x08
#define SCAN_END 0x77

#define BLINK_FEEDBACK_MS 300

extern uint8_t slaveCount;
extern uint8_t slaveList[112]; // max possible I2C slaves

void setupI2C();
void scanI2C();
void sendBlink(uint8_t addr);

#endif // !IIC_MANAGER_H
