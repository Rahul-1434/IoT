#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"
#define DHTPIN 19
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "ACENAARTECHNOLOGY"; 
const char* password = "123456789"; 
WiFiClient client;
unsigned long myChannelNumber = 1746705;
const char* myWriteAPIKey = "N0XKWYKGYZ75KC2S";
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
float temperature;
float humidity;

void readDHT() {
  int attempts = 0;
  while (attempts < 3) { 
    humidity = dht.readHumidity();
    temperature = dht.readTemperature(); 

    if (!isnan(humidity) && !isnan(temperature)) {
      Serial.print("Temperature (°C): ");
      Serial.println(temperature);
      Serial.print("Humidity (%): ");
      Serial.println(humidity);
      return;
    }
    else {
      Serial.println(F("Failed to read from DHT sensor! Retrying..."));
      attempts++;
      delay(1000); 
    }
  }
  Serial.println(F("Failed to read from DHT sensor after 3 attempts."));
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client); 
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  int wifiRetries = 0;
  while (WiFi.status() != WL_CONNECTED && wifiRetries < 20) {
    delay(5000);
    Serial.print(".");
    wifiRetries++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi.");
  } else {
    Serial.println("\nFailed to connect to WiFi. Exiting setup.");
    while (true); 
  }
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    readDHT();
    if (!isnan(humidity) && !isnan(temperature)) {
      ThingSpeak.setField(1, temperature);
      ThingSpeak.setField(2, humidity);
      int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      if (x == 200) {
        Serial.println("Channel update successful.");
      } else {
        Serial.println("Problem updating channel. HTTP error code " + String(x));
      }
    }
    lastTime = millis();
  }
}
