#define joyX 34
#define joyY 33
#include <ESP32Servo.h>

static const int servoPin = 23;
Servo servo1;
int pos = 0;
int xValue, yValue;

void setup() {
  Serial.begin(115200);
  Serial.println("Joy Stick in IDLE State");
  servo1.attach(servoPin);
}

void loop() {
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" Y: ");
  Serial.println(yValue);

  if (yValue < 100 && xValue > 2000 && xValue < 3000) {
    for (pos = 180; pos >= 0; pos -= 1) {
      servo1.write(pos);
      delay(20);
    }
    Serial.println("Right!!!");
  } else if (xValue < 100 && yValue > 2000 && yValue < 3000) {
    Serial.println("Up!!!");
  } else if (xValue > 4000 && yValue < 100) {
    for (pos = 0; pos <= 180; pos += 1) {
      servo1.write(pos);
      delay(20);
    }
    Serial.println("Left!!!");
  } else if (xValue > 4000 && yValue > 4000) {
    Serial.println("Down!!!!");
  } else {
    Serial.println("Idle State");
  }

  delay(100); 
}