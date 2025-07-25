// wifi_manager.h
#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h> // ESP32 WiFi
#include "globals.h" // For AppSettings, server, dnsServer, timeClient

// Function declarations
void connectWiFi();
void startAP();
void connectWifiStartAP();
void handleWifiConnection();

#endif // WIFI_MANAGER_H
