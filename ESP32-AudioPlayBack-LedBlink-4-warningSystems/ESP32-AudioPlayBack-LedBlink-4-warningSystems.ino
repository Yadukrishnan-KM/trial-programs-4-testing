// ESP32-AudioPlayBack-LedBlink-4-warningSystems.ino
/*
Project      : Audio play back and LED blink for warning systems in ESP32
Board        : ESP32 DevKit V1 (DOIT)
Author       : Yadukrishnan K M
Date Created : 2025-07-26
Last Update  : [YYYY-MM-DD]
IDE Version  : Arduino IDE 2.3.6             https://www.arduino.cc/en/software/
ESP32 Core   : Espressif ESP32 3.2.1         https://github.com/espressif/arduino-esp32
CPU Freq     : 240 MHz
Flash Freq   : 80 MHz
Libraries    :
  - Arduino.h (default)
Description  : It is a trial program and can use in other projetcs. It contains fuctions for blinking led in different rates and play audio 
using .h files via inbuilt DAC of ESP32. Pupose is for using in warnings for other systems.
*/

#include <Arduino.h>
#include "globals.h"
#include "DAC_LED_Warning.h"

unsigned long timeOld = 0; // for changing the led blinking rates in a loop
int number = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  dacWrite(dacPin, 0); // make audio mute
}

void loop() {
  // Your loop code here
  // for testing led blink
  unsigned long timeNow = millis();
  if((timeNow - timeOld) >= 5000){
    if(number == 0){
      setLEDBlink(1,2,1);
      number++;
    }
    else if(number == 1){
      setLEDBlink(2,1,0);
      number++;
    }
    else if(number == 2){
      setLEDBlink(2,0,0);
      number++;
    }
    else{
      setLEDBlink(0,0,0);
      number = 0;
    }
  timeOld = timeNow;
  }
  //systemError = true;
  ledDrive();

  /*// for testing the audio play through inbuilt DAC
  AudioWarning(audioData_level1breach,audioLength_level1breach,sampleRate);
  delay(500);
  AudioWarning(audioData_level2breach,audioLength_level2breach,sampleRate);
  delay(500);
  AudioWarning(audioData_level3breach,audioLength_level3breach,sampleRate);
  delay(500);*/
}
