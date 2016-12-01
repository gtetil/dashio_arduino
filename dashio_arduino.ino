
int digitalInputs = 0;
int serialRead = 0;  //was "byte"  !!!!!!!!!!!!!!!!!!!



void setup() {
  
  Serial.begin(115200);  

  pinMode(5, OUTPUT);   //DO0
  pinMode(6, OUTPUT);   //DO1
  pinMode(7, OUTPUT);   //DO2
  pinMode(8, OUTPUT);   //DO3
  pinMode(9, OUTPUT);   //DO4
  pinMode(10, OUTPUT);  //DO5
  //pinMode(11, OUTPUT);  //DO6
  //pinMode(12, OUTPUT);  //DO7
  pinMode(2, INPUT);  //DI4
  pinMode(3, INPUT);  //DI5
  pinMode(4, INPUT);  //IGN_IN

}

void loop() {

  //read digital DI's
  for (int pin = 4; pin >= 2; pin--) {
    digitalInputs |= !digitalRead(pin);
    digitalInputs = digitalInputs << 1;
  }

  //read analog DI's
  for (int pin = 5; pin >= 2; pin--) {
    int aiValue = analogRead(pin);
    int aiState = 0;
    if (aiValue < 128) {
      aiState = 1;
    }
    digitalInputs |= aiState;
    digitalInputs = digitalInputs << 1;
  }
  
  digitalInputs = digitalInputs >> 1;
  Serial.print(digitalInputs);
  Serial.print("\n");
  digitalInputs = 0;

  delay(100);

  while (Serial.available() > 0) {
    String command = Serial.readStringUntil('/');
    
    if (command == "digital") {
      digitalCommand();
    }
  }
}  
  
void digitalCommand() {
    
  int digitalIndex = Serial.parseInt();
    
  int digitalValue = Serial.parseInt();
    
  int pin = digitalIndex + 5;
    
  digitalWrite(pin, digitalValue);
  
}

