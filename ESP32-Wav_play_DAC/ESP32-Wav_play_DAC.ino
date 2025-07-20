#include <Arduino.h>
extern const uint8_t audioData[];
extern const size_t audioLength;

const int sampleRate = 8000; // Hz
const int dacPin = 25;       // DAC1 = GPIO25

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Playing audio...");
  playAudio(audioData, audioLength, sampleRate);
}

void loop() {
  // Play again after 10 sec for test
  delay(10000);
  playAudio(audioData, audioLength, sampleRate);
}

void playAudio(const uint8_t* data, size_t len, int rate) {
  int delayMicros = 1000000 / rate;

  for (size_t i = 0; i < len; i++) {
    dacWrite(dacPin, data[i]);
    delayMicroseconds(delayMicros);
  }

  dacWrite(dacPin, 0); // mute
}
