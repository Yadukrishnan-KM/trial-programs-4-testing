// globals.cpp
#include "globals.h"

// ============================================================================
// Global Variable Definitions
// ============================================================================
// Audio warning variable definition
const size_t audioLength_level1breach = sizeof(audioData_level1breach);
const size_t audioLength_level2breach = sizeof(audioData_level2breach);
const size_t audioLength_level3breach = sizeof(audioData_level3breach);
const int sampleRate = 16000; // Hz
const int dacPin = 25;       // DAC1 = GPIO25

// LED blink variable definition 
const int ledPin = 2;  // ESP32 inbuilt LED
bool ledOn = false;
unsigned long lastBlinkTime = 0;
const int level1BlinkDelay = 110; // the time in ms, on or off time
const int level2BlinkDelay = 400; // the time in ms, on or off time
const int level3BlinkDelay = 1100; // the time in ms, on or off time
int blinkDelay = level3BlinkDelay;
bool systemError = false;
LedState ledState = LED_IDLE;

// Initialize global objects
