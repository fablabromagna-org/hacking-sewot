#include <Arduino.h>

void win() {
  Serial.println("YOU WIN!");
}

void setup() {
  Serial.begin(115200);
  delay(5000);
  win();
}

void loop() {
  Serial.println("I'm useless, lol.");
  delay(5000);
}
