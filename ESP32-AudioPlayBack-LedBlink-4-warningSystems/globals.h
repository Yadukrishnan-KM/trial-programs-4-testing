// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

// ============================================================================
// 1. Necessary Includes at the Top
//    (Order matters for some dependencies)
// ============================================================================
#include <Arduino.h>           
#include "level1breach.h"
#include "level2breach.h"
#include "level3breach.h"

// Audio warning related declaration
extern const size_t audioLength_level1breach;
extern const size_t audioLength_level2breach;
extern const size_t audioLength_level3breach;
extern const int sampleRate;
extern const int dacPin;

// LED Blink related declaration
extern const int ledPin;
extern int blinkDelay;
extern bool ledOn;
extern unsigned long lastBlinkTime;
extern const int level1BlinkDelay ;
extern const int level2BlinkDelay ;
extern const int level3BlinkDelay ;
extern bool systemError;
// Type declaration
typedef enum LedState { LED_IDLE, LED_BLINKING };
extern LedState ledState;
// Object declaration

#endif // GLOBALS_H
