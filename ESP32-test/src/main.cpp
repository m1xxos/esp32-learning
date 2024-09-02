#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin();
  Serial.println("hello");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("hello loop");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}
