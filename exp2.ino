#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

#define trigPin 23
#define echoPin 39

long duration;
int distance;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    distance = -1;
  } else {
    distance = duration * 0.034 / 2;
  }

  Serial.print("Distance: ");
  if (distance == -1) {
    Serial.println("Out of range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");

  if (distance == -1) {
    lcd.setCursor(9, 0);
    lcd.print("Out of range");
  } else {
    lcd.setCursor(9, 0);
    lcd.print(distance);
    lcd.setCursor(13, 0);
    lcd.print("CM");
  }

  delay(500);
}