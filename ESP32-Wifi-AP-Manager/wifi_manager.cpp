// wifi_manager.cpp
#include "wifi_manager.h"
/**
 * @brief Connects to WiFi and start time client for receiving time
 */
void connectWiFi() {
  Serial.print(F("Connecting to WiFi: "));
  Serial.println(STA_SSID);
  Serial.println(STA_PASSWORD);

  WiFi.mode(WIFI_STA);
  WiFi.begin(STA_SSID, STA_PASSWORD);

  int attempts = 0; // to avoid endless operation of while loop
  while (WiFi.status() != WL_CONNECTED && attempts < 40) {  // Try for 20 seconds
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("\nWiFi connected."));
    Serial.print(F("IP Address: "));
    Serial.println(WiFi.localIP());
    timeClient.begin();  // Start NTP client once connected
  } else {
    Serial.println(F("\nFailed to connect to WiFi."));
  }
}

/**
 * @brief Starts Access Point (AP) mode for webserver
 */
void startAP() {
  WiFi.mode(WIFI_AP);
  // Setting up static IP for the AP
  WiFi.softAPConfig(local_IP, gateway, subnet);
  // Setting up name and password for the AP
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  Serial.print(F("AP Started. IP Address: "));
  Serial.println(WiFi.softAPIP());

  // DNS server for captive portal
  dnsServer.start(53, "*", WiFi.softAPIP());
}

/**
 * @brief Starts WiFi and Access Point (AP) mode together for internet access and webserver
 */
void connectWifiStartAP() {
  Serial.print(F("Connecting to WiFi: "));
  Serial.print(STA_SSID);
  Serial.print(STA_PASSWORD);
  WiFi.mode(WIFI_AP_STA);
  // Use currentSettings for SSID and password
  WiFi.begin(STA_SSID, STA_PASSWORD);

  int attempts = 0; // to avoid endless operation of while loop
  while (WiFi.status() != WL_CONNECTED && attempts < 40) {  // Try for 20 seconds
    delay(500);
    Serial.print(".");
    attempts++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("\nWiFi connected."));
    Serial.print(F("IP Address: "));
    Serial.println(WiFi.localIP());
    timeClient.begin();  // Start NTP client once connected
  } else {
    Serial.println(F("\nFailed to connect to WiFi."));
  }
  WiFi.softAPConfig(local_IP, gateway, subnet);
  // Setting up name and password for the AP
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  Serial.print(F("AP Started. IP Address: "));
  Serial.println(WiFi.softAPIP());

  // DNS server for captive portal
  dnsServer.start(53, "*", WiFi.softAPIP());
}

/**
 * @brief Handles WiFi connection status in the loop.
 * In STA mode or AP_STA and disconnected, attempts to reconnect.
 */
void handleWifiConnection() {
  if (WiFi.status() != WL_CONNECTED && (WiFi.getMode() == WIFI_STA || WiFi.getMode() == WIFI_AP_STA)) {
    Serial.println(F("WiFi disconnected. Attempting to reconnect..."));
    WiFi.reconnect();
    // A short delay might be useful here to prevent aggressive re-connection attempts
    delay(100);
  }
}
