// globals.cpp
#include "globals.h"

// ============================================================================
// Global Variable Definitions
// ============================================================================

// WiFi definitions, ONLY here (user field)
const char* STA_SSID = "OnePlus NordCE 5G";
const char* STA_PASSWORD = "c67hu553";

// AP definitions, ONLY here (user field)
const char* AP_SSID = "ESP32_AP";
const char* AP_PASSWORD = "password123";
IPAddress local_IP(192,168,10,1);
IPAddress gateway(192,168,10,1);
IPAddress subnet(255,255,255,0);

// Initialize global objects
DNSServer dnsServer;
WiFiUDP ntpUdp;
NTPClient timeClient(ntpUdp, "pool.ntp.org", UTC_OFFSET_SECONDS);
