#define Relay 19
#define LIGHT_SENSOR_PIN 34
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(Relay, OUTPUT);
}

void loop() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.print("Analog Value = ");
  Serial.println(analogValue);
  lcd.setCursor(0, 0);
  lcd.print("Light Intensity");
  lcd.setCursor(0, 1);
  lcd.print(analogValue);

  if (analogValue < 500) {
    Serial.println("Relay ON");
    digitalWrite(Relay, LOW);
  } else {
    Serial.println("Relay OFF");
    digitalWrite(Relay, HIGH);
  }

  delay(1000);
}