#define BLUE_PIN 16
#define RED_PIN 22
#define GREEN_PIN 23

void setup() {
  // put your setup code here, to run once:
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void loop() {
  // Включаем светодиод
  digitalWrite(BLUE_PIN, HIGH);
  delay(1000); // Задержка 1 секунда
  
  // Выключаем светодиод
  digitalWrite(BLUE_PIN, LOW);
  delay(1000); // Задержка 1 секунда

  digitalWrite(RED_PIN, HIGH);
  delay(1000); // Задержка 1 секунда
  
  // Выключаем светодиод
  digitalWrite(RED_PIN, LOW);
  delay(1000); // Задержка 1 секунда

  digitalWrite(GREEN_PIN, HIGH);
  delay(1000); // Задержка 1 секунда
  
  // Выключаем светодиод
  digitalWrite(GREEN_PIN, LOW);
  delay(1000); // Задержка 1 секунда
}
