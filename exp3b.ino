#include "DHT.h"
#define DHTPIN 19
#define DHTTYPE DHT11
#include <LiquidCrystal_I2C.h>
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3f, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop() {
  delay(2000);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(humidity) || isnan(temperature) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("% Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C "));

  lcd.setCursor(0, 0);
  lcd.print("Temp");
  lcd.setCursor(5, 0);
  lcd.print((char)223);
  lcd.setCursor(6, 0);
  lcd.print("C");
  lcd.setCursor(9, 0);
  lcd.print("Humi %");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.setCursor(9, 1);
  lcd.print(humidity);
}
