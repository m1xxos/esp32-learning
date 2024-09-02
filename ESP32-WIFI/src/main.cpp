#include <Arduino.h>
#include <WiFiMulti.h>
#include <WebServer.h>
#include <config.h>

WebServer server(80); // Создаем сервер на порту 80

const int ledPin = 16; // Измените это значение в зависимости от вашего подключения

// Флаг для отслеживания состояния светодиода
bool ledState = false;

// Функция для обработки корневого пути "/"
void handleRoot() {
    String html = "<html><body><h1>ESP32 LED Control</h1>";
    html += "<button onclick=\"toggleLED()\">Toggle LED</button>";
    html += "<script>";
    html += "function toggleLED() {";
    html += "var xhttp = new XMLHttpRequest();";
    html += "xhttp.open('GET', '/toggle', true);";
    html += "xhttp.send();";
    html += "}";
    html += "</script></body></html>";

    server.send(200, "text/html", html);
}

// Функция для обработки пути "/toggle"
void handleToggle() {
    ledState = !ledState;  // Меняем состояние светодиода на противоположное
    digitalWrite(ledPin, ledState ? HIGH : LOW);  // Устанавливаем состояние светодиода
    server.send(200, "text/plain", ledState ? "LED is ON" : "LED is OFF");
}

// Обработчик для ошибки 404 - страница не найдена
void handleNotFound() {
    server.send(404, "text/plain", "404: Not found");
}

WiFiMulti wifiMulti;

void setup() {
  Serial.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);


  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED)
  {
    delay(1000);
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());

  // Определяем обработчики
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.onNotFound(handleNotFound);

  // Запускаем сервер
  server.begin();
  Serial.println("HTTP server started");
  
}

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
  server.handleClient();
}
