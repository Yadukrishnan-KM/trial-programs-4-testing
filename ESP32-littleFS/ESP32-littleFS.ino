
/*
Project      : ESP32-littleFS
Board        : ESP32 DevKit V1 (DOIT)
Author       : Yadukrishnan K M
Date Created : 22-07-2025
Last Update  : 23-07-2025
IDE Version  : Arduino IDE 2.3.6             https://www.arduino.cc/en/software/
ESP32 Core   : Espressif ESP32 3.2.1         https://github.com/espressif/arduino-esp32
CPU Freq     : 240 MHz
Flash Freq   : 80 MHz
Libraries    :
  - Arduino.h (default)
  - 
Description  : It is a trial program to check the operation of littleFs file system.
We will upload a file (present in the data folder in the project root) using the 
uploading tool using terminal and the given code will show the list of files in the root folder 
inside the file system. 

The file upload procedure is in the project folder.
*/
#include <Arduino.h>
#include "FS.h"
#include "LittleFS.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- LittleFS Test Program ---");

  // Initialize LittleFS
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS mount failed!");
  } else {
    Serial.println("LittleFS mounted successfully.");
    Serial.println("\n--- Listing Files in LittleFS ---");
    listFiles();
    Serial.println("\n--- LittleFS Test Program End ---");
  }
}

void loop() {
  // Nothing to do in the loop for this example
}


void listFiles() {
  // Use the Dir class directly from the LittleFS object
  // This syntax works across many ESP32 core versions for LittleFS.
  File dir = LittleFS.open("/");  // Open root directory as a File object
  if (!dir) {
    Serial.println("Failed to open root directory!");
    return;
  }

  bool filesFound = false;
  // Iterate through the directory
  while (File entry = dir.openNextFile()) {
    if (entry.isDirectory()) {
      Serial.printf("  Dir: %s\n", entry.name());
    } else {
      Serial.printf("  File: %s, Size: %u bytes\n", entry.name(), entry.size());
    }
    filesFound = true;
  }

  if (!filesFound) {
    Serial.println("No files found in LittleFS. It is empty.");
  }
}

// more available functions if required.

/*
void createSampleFile(const char* path, const char* content) {
  if (LittleFS.exists(path)) {
    Serial.printf("File '%s' already exists. Skipping creation.\n", path);
    return;
  }

  Serial.printf("Creating file: %s\n", path);
  File file = LittleFS.open(path, "w");
  if (!file) {
    Serial.println("Failed to open file for writing.");
    return;
  }
  file.print(content);
  file.close();
  Serial.printf("File '%s' created successfully.\n", path);
}
usage:
createSampleFile("/file1.txt", "This is the content of file 1.");

void readFileContent(const char* path) {
  Serial.printf("\nReading content of file: %s\n", path);
  File file = LittleFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open file for reading.");
    return;
  }
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
  Serial.println("\n--- End of file content ---");
}

void deleteFile(const char* path) {
  Serial.printf("\nDeleting file: %s\n", path);
  if (LittleFS.remove(path)) {
    Serial.println("File deleted successfully.");
  } else {
    Serial.println("Failed to delete file.");
  }
}

// some other useful commands

LittleFS.format()

*/
