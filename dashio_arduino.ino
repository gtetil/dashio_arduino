
//digital output pins
int do_0_pin = 5;
int do_1_pin = 6;
int do_2_pin = 7;
int do_3_pin = 8;
int do_4_pin = 9;
int do_5_pin = 10;

//digital input pins
int di_0_pin = 5; //analog input
int di_1_pin = 4; //analog input
int di_2_pin = 3; //analog input
int di_3_pin = 2; //analog input
int di_4_pin = 2;
int di_5_pin = 3;
int ignition_pin = 4;

//digital output states
int do_0_state = 0;
int do_1_state = 0;
int do_2_state = 0;
int do_3_state = 0;
int do_4_state = 0;
int do_5_state = 0;

//digital input states
int di_0_state = 0; //analog input
int di_1_state = 0; //analog input
int di_2_state = 0; //analog input
int di_3_state = 0; //analog input
int di_4_state = 0;
int di_5_state = 0;
int ignition_state = 0;

//misc
int ai_threshold = 128;
unsigned long main_timer = millis();
String data_string;

void setup() {
  
  Serial.begin(115200);  

  pinMode(do_0_pin, OUTPUT);
  pinMode(do_1_pin, OUTPUT);
  pinMode(do_2_pin, OUTPUT);
  pinMode(do_3_pin, OUTPUT);
  pinMode(do_4_pin, OUTPUT);
  pinMode(do_5_pin, OUTPUT);
  pinMode(di_4_pin, INPUT);
  pinMode(di_5_pin, INPUT);
  pinMode(ignition_pin, INPUT);
}

void loop() {

  if ((millis() - main_timer) >= 100) {
    main_timer = millis();
    digitalInputs();
    sendData();
  }
  
  checkSerial();

  //if ignition is off, then turn off all digital outputs
  if (ignition_state == 0) {
    killAllOutputs();
  }
  
}  

void sendData() {
  data_string = "";
  addStringData(String(di_0_state));
  addStringData(String(di_1_state));
  addStringData(String(di_2_state));
  addStringData(String(di_3_state));
  addStringData(String(di_4_state));
  addStringData(String(di_5_state));
  addStringData(String(ignition_state));
  Serial.println(data_string);
}  

void addStringData(String data) {
  data_string += data + ",";
}

void digitalInputs() {
  di_0_state = readAnalogDI(di_0_pin);
  di_1_state = readAnalogDI(di_1_pin);
  di_2_state = readAnalogDI(di_2_pin);
  di_3_state = readAnalogDI(di_3_pin);
  di_4_state = !digitalRead(di_4_pin);
  di_5_state = !digitalRead(di_5_pin);
  ignition_state = !digitalRead(ignition_pin);
}

int readAnalogDI(int pin) {
  int aiValue = analogRead(pin);
  int aiState = 0;
  if (aiValue < ai_threshold) {
    aiState = 1;
  }
  return aiState;
}

void checkSerial() {
  while (Serial.available() > 0) {
    String command = Serial.readStringUntil('/');
    
    if (command == "digital_output") {
      String tag = Serial.readStringUntil('/');
      int state = Serial.parseInt();
      digitalOutput(tag, state);
    }
  }
}

void digitalOutput(String tag, int state) {
  if (tag == "DO_0") {
    do_0_state = state;
    digitalWrite(do_0_pin, state);
  }
  else if (tag == "DO_1") {
    do_1_state = state;
    digitalWrite(do_1_pin, state);
  }
  else if (tag == "DO_2") {
    do_2_state = state;
    digitalWrite(do_2_pin, state);
  }
  else if (tag == "DO_3") {
    do_3_state = state;
    digitalWrite(do_3_pin, state);
  }
  else if (tag == "DO_4") {
    do_4_state = state;
    digitalWrite(do_4_pin, state);
  }
  else if (tag == "DO_5") {
    do_5_state = state;
    digitalWrite(do_5_pin, state);
  }
}

void killAllOutputs() {
  digitalOutput("DO_0", 0);
  digitalOutput("DO_1", 0);
  digitalOutput("DO_2", 0);
  digitalOutput("DO_3", 0);
  digitalOutput("DO_4", 0);
  digitalOutput("DO_5", 0);
}

