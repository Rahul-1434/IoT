#define Buzzer 19

void setup() {
  Serial.begin(9600); 
  pinMode(Buzzer, OUTPUT); 
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    int myInt = command.toInt(); 
    Serial.println(myInt); 

    if (myInt == 1) {
      digitalWrite(Buzzer, HIGH); 
      Serial.println("Buzzer ON");
    } 
    else if (myInt == 0) {
      digitalWrite(Buzzer, LOW); 
      Serial.println("Buzzer OFF");
    }
  }
}
