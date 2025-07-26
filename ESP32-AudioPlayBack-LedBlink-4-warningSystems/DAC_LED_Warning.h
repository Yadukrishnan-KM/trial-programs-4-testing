// DAC_LED_Warning.h
#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include "globals.h" 

// Function declarations
void AudioWarning(const uint8_t* data, size_t len, int rate);
void setLEDBlink(int l3, int l2, int l1);
void ledDrive();

#endif // WIFI_MANAGER_H
