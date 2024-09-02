#include <Arduino.h>
#include <WiFiMulti.h>

#define WIFI_SSID "ESP-Guest"
#define WIFI_PASSWORD "123456789"

WiFiMulti wifiMulti;

void setup() {
  Serial.begin();
  pinMode(LED_BUILTIN, OUTPUT);

  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED)
  {
    delay(1000);
  }

  Serial.println("Connected");
  
}

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
}
