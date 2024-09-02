#include <Arduino.h>
#include <WiFiMulti.h>
#include <WebServer.h>
#include <config.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


WebServer server(80); 

const int ledPin = 16; 

bool ledState = false;


void handleRoot() {
    String html = "<html><body><h1>ESP32 LED and Display Control</h1>";
    html += "<button onclick=\"toggleLED()\">Toggle LED</button>";
    html += "<form action=\"/submit\" method=\"get\">";
    html += "<input type=\"text\" name=\"text\" placeholder=\"Enter text\">";
    html += "<input type=\"submit\" value=\"Submit\">";
    html += "</form>";
    html += "<script>";
    html += "function toggleLED() {";
    html += "var xhttp = new XMLHttpRequest();";
    html += "xhttp.open('GET', '/toggle', true);";
    html += "xhttp.send();";
    html += "}";
    html += "</script></body></html>";

    server.send(200, "text/html", html);
}


void handleToggle() {
    ledState = !ledState;  
    digitalWrite(ledPin, ledState ? HIGH : LOW);  
    server.send(200, "text/plain", ledState ? "LED is ON" : "LED is OFF");
}

void handleSubmit() {
    if (server.hasArg("text")) {
        String text = server.arg("text");  // Получаем текст из формы
        Serial.println("Received text: " + text);

        // Отображаем текст на дисплее
        display.clearDisplay();
        display.setTextSize(1);  // Размер текста
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0); // Позиция курсора
        display.println(text);
        display.display();

        server.send(200, "text/html", "<html><body><h1>Text Displayed!</h1><a href=\"/\">Back</a></body></html>");
    } else {
        server.send(400, "text/plain", "No text received");
    }
}

void handleNotFound() {
    server.send(404, "text/plain", "404: Not found");
}

WiFiMulti wifiMulti;

void setup() {
  Serial.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);  // Остановка в случае ошибки
    }
    display.display();


  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED)
  {
    delay(1000);
  }
  Serial.println("Connected");
  Serial.println(WiFi.localIP());

  
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/submit", handleSubmit);
  server.onNotFound(handleNotFound);

  
  server.begin();
  Serial.println("HTTP server started");
  
}

void loop() {
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
  server.handleClient();
}
