// ESP32-WifiManager.ino
/*
Project      : ESP32-Wifi manager trial
Board        : ESP32 DevKit V1 (DOIT)
Author       : Yadukrishnan K M
Date Created : 25-07-2025
Last Update  : 25-07-2025
IDE Version  : Arduino IDE 2.3.6             https://www.arduino.cc/en/software/
ESP32 Core   : Espressif ESP32 3.2.1         https://github.com/espressif/arduino-esp32
CPU Freq     : 240 MHz
Flash Freq   : 80 MHz
Libraries    :
  - Arduino.h (default)
  - 
Description  : It is a program to test the wifi station and wifi access point and wifi and Ap together. Also using NTP for time access.
*/

#include <Arduino.h>
#include "wifi_manager.h"
#include "globals.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // just checking all functions
  connectWiFi();
  Serial.println(F("WiFi disconnecting..."));
  WiFi.disconnect(true);

  startAP();
  Serial.println(F("AP stopping..."));
  dnsServer.stop();
  WiFi.softAPdisconnect(true);

  connectWifiStartAP();
  Serial.println(F("WiFi and AP stopping..."));
  dnsServer.stop();
  WiFi.softAPdisconnect(true);

  WiFi.disconnect(true);
  connectWifiStartAP();
}

void loop() {
  // put your main code here, to run repeatedly:
  handleWifiConnection();
 
}
