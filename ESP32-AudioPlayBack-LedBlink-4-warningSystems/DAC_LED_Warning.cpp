// DAC_LED_Warning.cpp
#include "DAC_LED_Warning.h"
/**
 * @brief Audio playing function from .h file using internal DAC
 * @param .h file, audioLength, sampling rate
 * Global Variables: dacPin
 * Note: Starting time in void setup make the dacPin to zero, (dacWrite(dacPin, 0);)
 */

void AudioWarning(const uint8_t* data, size_t len, int rate) {
  int delayMicros = 1000000 / rate;

  for (size_t i = 0; i < len; i++) {
    dacWrite(dacPin, data[i]);
    delayMicroseconds(delayMicros);
  }

  dacWrite(dacPin, 0);  // mute 
}
/**
 * @brief LED status setting function, call when required to change the blinking rate
 * @param 3 different warning levels(l1-high priority), if breach present it will activates the blink rate
 * Global Variables: blinkDelay, level1BlinkDelay, level2BlinkDelay, level3BlinkDelay, ledState
 */

void setLEDBlink(int l3, int l2, int l1) {
  if (l1 > 0) blinkDelay = level1BlinkDelay ; // high priority breach
  else if (l2 > 0) blinkDelay = level2BlinkDelay ;
  else if (l3 > 0) blinkDelay = level3BlinkDelay ; // low priority breach
  else {
    ledState = LED_IDLE;
    return;
  }
  ledState = LED_BLINKING;
}
/**
 * @brief LED digitalWrite doing function, blinking is inside implemeted using millis(), call continiously in the loop
 * Note: ensure that ledPin function defined as DigitalOut in the void setup() function (pinMode(ledPin, OUTPUT);)
 * Global variables required: ledPin, systemError, ledState, lastBlinkTime, blinkDelay, ledOn
 */

void ledDrive(){
  // LED always ON for error condition
  if(systemError){
    digitalWrite(ledPin, HIGH); 
  }
  else{
    if(ledState == LED_IDLE) digitalWrite(ledPin, LOW);
    else if(ledState == LED_BLINKING){
      unsigned long now = millis();
      if((now - lastBlinkTime) >= blinkDelay){
        digitalWrite(ledPin, ledOn ? HIGH : LOW);
        lastBlinkTime = now;
        ledOn = !ledOn; // for making the led state memory to alternate state
      }
    }
  }
}