#include <Arduino.h>
#include <WiFiMulti.h>
#include <WebServer.h>
#include <config.h>

WebServer server(80); // Создаем сервер на порту 80

// Обработчик для главной страницы
void handleRoot() {
    server.send(200, "text/html", "<h1>Welcome to ESP32 Web Server!</h1>");
}

// Обработчик для ошибки 404 - страница не найдена
void handleNotFound() {
    server.send(404, "text/plain", "404: Not found");
}

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
  Serial.println(WiFi.localIP());

  // Определяем обработчики
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  // Запускаем сервер
  server.begin();
  Serial.println("HTTP server started");
  
}

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
  server.handleClient();
}
