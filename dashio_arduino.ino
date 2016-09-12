
int digitalInputs = 0;
byte serialRead = 0;


void setup() {
  
  Serial.begin(115200);  

  pinMode(5, OUTPUT);   //DO0
  pinMode(6, OUTPUT);   //DO1
  pinMode(7, OUTPUT);   //DO2
  pinMode(8, OUTPUT);   //DO3
  pinMode(9, OUTPUT);   //DO4
  pinMode(10, OUTPUT);  //DO5
  pinMode(11, OUTPUT);  //DO6
  pinMode(12, OUTPUT);  //DO7
  pinMode(2, INPUT);  //DI6
  pinMode(3, INPUT);  //DI7
  pinMode(4, INPUT);  //IGN_IN

}

void loop() {

  //read digital DI's
  for (int pin = 4; pin >= 2; pin--) {
    digitalInputs |= digitalRead(pin);
    digitalInputs = digitalInputs << 1;
  }

  //read analog DI's
  for (int pin = 5; pin >= 0; pin--) {
    int aiValue = analogRead(pin);
    int aiState = 0;
    if (aiValue < 128) {
      aiState = 1;
    }
    digitalInputs |= aiState;
    digitalInputs = digitalInputs << 1;
  }
  
  digitalInputs = ~digitalInputs; //invert DI integer

  Serial.write(digitalInputs);

  delay(100);

  while (Serial.available() > 0) {
    serialRead = Serial.read();
    for (int i = 0; i < 7; i++) {
      int mask = 1 << i;
      int state = serialRead & mask;
      state = state >> i;
      int pin = i + 5;
      digitalWrite(pin, state);
    }   
  }
}
