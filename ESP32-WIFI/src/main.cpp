#include <WiFi.h>
#include <ModbusIP_ESP8266.h> // Используем ту же библиотеку для Modbus
#include <DHT.h>
#include <config.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>

// Настройки DHT22
#define DHTPIN D4      // Пин, к которому подключен DHT22 (на XIAO ESP32-C6 используйте D6)
#define DHTTYPE DHT22  // Тип датчика

DHT dht(DHTPIN, DHTTYPE);

// Modbus
ModbusIP mb;

void setup() {
  Serial.begin(115200);

  // Инициализация DHT22
  dht.begin();

  // Подключение к Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());  // Вывод IP-адреса ESP32-C6

  // Инициализация Modbus
  mb.server();
  mb.addHreg(0);  // Holding Register 0 для температуры
  mb.addHreg(1);  // Holding Register 1 для влажности
}

void loop() {
  // Чтение температуры и влажности
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Проверка на ошибки чтения
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Ошибка чтения датчика!");
    return;
  }

  // Вывод данных в Serial Monitor
  Serial.print("Температура: ");
  Serial.print(temperature);
  Serial.print(" °C, Влажность: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Запись температуры и влажности в Modbus-регистры
  mb.Hreg(0, (int)(temperature * 10));  // Температура (умножаем на 10 для точности)
  mb.Hreg(1, (int)(humidity * 10));     // Влажность (умножаем на 10 для точности)

  // Обновление Modbus
  mb.task();
  delay(2000);  // Пауза между измерениями
}