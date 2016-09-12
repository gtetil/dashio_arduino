
byte digitalInputs = 0;
byte serialRead = 0;


void setup() {
  
  Serial.begin(115200);  

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

}

void loop() {

  digitalInputs |= 1;
  digitalInputs = digitalInputs << 1;
  digitalInputs |= 1;
  digitalInputs = digitalInputs << 1;
  digitalInputs |= digitalRead(9);
  digitalInputs = digitalInputs << 1;
  digitalInputs |= digitalRead(8);
  digitalInputs = digitalInputs << 1;
  digitalInputs |= digitalRead(7);
  digitalInputs = digitalInputs << 1;
  digitalInputs |= digitalRead(6);
  digitalInputs = ~digitalInputs;

  Serial.write(digitalInputs);

  delay(100);

  while (Serial.available() > 0) {
    serialRead = Serial.read();
    for (int i = 0; i < 4; i++) {
      int mask = 1 << i;
      int state = serialRead & mask;
      state = state >> i;
      int pin = i + 2;
      digitalWrite(pin, state);
    }   
  }
}
