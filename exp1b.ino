#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {32, 33, 25, 26}; 
byte colPins[COLS] = {27, 14, 12}; 


Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


const int pins[8] = {15, 2, 4, 16, 17, 5, 18, 19};


int counterValue = 1;
int rightShiftValue = 0;
int extractLSB;
int n = 0;

void setup() {
  for (int ii = 0; ii < 8; ii++) {
    pinMode(pins[ii], OUTPUT);
  }
  allOff();
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    switch (key) {
      case '1': 
        allOn();
        break;
      case '2': 
        allOff();
        break;
      case '3': 
        allOff();
        for (int ii = 1; ii <= 5; ii++) 
          blinkAll();
        break;
      case '4': 
        allOff();
        for (int ii = 1; ii <= 5; ii++) 
          ledWalk();
        break;
      case '5': 
        allOff();
        binaryCounter();
        break;
    }
  }
}

void allOff() {
  for (int ii = 0; ii < 8; ii++) {
    digitalWrite(pins[ii], LOW);
  }
}

void allOn() {
  for (int ii = 0; ii < 8; ii++) {
    digitalWrite(pins[ii], HIGH);
  }
}

void blinkAll() {
  for (int ii = 0; ii < 8; ii++) {
    digitalWrite(pins[ii], HIGH);
  }
  delay(500);
  for (int ii = 0; ii < 8; ii++) {
    digitalWrite(pins[ii], LOW);
  }
  delay(500);
}

void ledWalk() {
  for (int ii = 0; ii < 8; ii++) {
    digitalWrite(pins[ii], LOW);
    delay(70);
  }
  for (int ii = 0; ii < 8; ii++) {
    delay(70);
    digitalWrite(pins[ii], HIGH);
  }
}

void driveCounter(int counterValue) {
  int rightShiftValue, extractLSB;
  for (int ii = 0; ii < 8; ii++) {
    rightShiftValue = counterValue >> ii;
    extractLSB = rightShiftValue & 0x1;
    if (extractLSB == 1) {
      digitalWrite(pins[ii], LOW);
    } else {
      digitalWrite(pins[ii], HIGH);
    }
  }
}

void binaryCounter() {
  for (int ii = 1; ii <= 255; ii++) {
    driveCounter(ii);
    delay(100);
  }
}