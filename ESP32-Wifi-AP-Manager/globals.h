// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

// ============================================================================
// 1. Necessary Includes at the Top
//    (Order matters for some dependencies, e.g., NTPClient needs WiFiUdp)
// ============================================================================
#include <Arduino.h>           
#include <DNSServer.h>        // For DNSServer
#include <WiFiUdp.h>          // For WiFiUDP (NTPClient depends on this)
#include <NTPClient.h>        // For NTPClient
//#include <ESPmDNS.h>          // For mDNS on ESP32

// WiFi STA declaration
extern const char* STA_SSID;
extern const char* STA_PASSWORD;

// AP delclaration
extern const char* AP_SSID;
extern const char* AP_PASSWORD;
extern IPAddress local_IP;
extern IPAddress gateway;
extern IPAddress subnet;

// Object declaration
extern DNSServer dnsServer;
extern WiFiUDP ntpUdp;
extern NTPClient timeClient;

// Constants
const long UTC_OFFSET_SECONDS = 5.5 * 3600; // IST is UTC+5:30

#endif // GLOBALS_H
