#ifndef IIC_MANAGER_H
#define IIC_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#define PERIPHERAL_ADDRESS 0x1C

void setupI2C();
void scanForI2CDevices();
void sendMessageFromSerial(byte address);

#endif // !IIC_MANAGER_H
