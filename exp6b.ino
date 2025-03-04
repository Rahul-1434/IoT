#define BLYNK_DEVICE_NAME "HomeAutomation" 
#define BLYNK_PRINT Serial 
#define BLYNK_TEMPLATE_ID "TMPL3vTmEPAPP"
#define BLYNK_TEMPLATE_NAME "Buzzer"
#define BLYNK_AUTH_TOKEN "Y8XhxeuJEYOeHGOeyP5NCfDvHMf9itI8"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "User"; 
char pass[] = "12345678"; 
int Buzzer = 19; 
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0); 
}

BLYNK_WRITE(V0) {
  int value = param.asInt(); 
  Serial.println(value);
  
  if (value == 1) {
    digitalWrite(Buzzer, HIGH); 
    Serial.println("Buzzer ON");
  } else {
    digitalWrite(Buzzer, LOW); 
    Serial.println("Buzzer OFF");
  }
}

void setup() {
  pinMode(Buzzer, OUTPUT); 
  Serial.begin(9600); 
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    wifi_ctr++;
    if (wifi_ctr > 30) { 
      Serial.println("Wi-Fi connection failed.");
      return;
    }
  }
  
  Serial.println("Wi-Fi connected");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); 
}

void loop() {
  Blynk.run(); 
}
