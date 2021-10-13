int PINS[] = { 9, 10, 11};
/*
int PIN_BLUE = 9, 
  PIN_GREEN = 10, 
  PIN_RED = 11;
*/
int dc = 255;

// dc = duty cycle [0; 255]
void pwm(int pin, int dc) {
  float T = 255.0;
  float c = T / dc;
  digitalWrite(pin, HIGH);
  delayMicroseconds(dc * c);
  digitalWrite(pin, LOW);
  delayMicroseconds((T - dc)*c);
}

void print_pin(int pin, int value) {
  Serial.print(pin);
  Serial.print(" = ");
  Serial.print(value);
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(PINS[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < sizeof(PINS) / sizeof(PINS[0]); i++) {
    int pin_value = PINS[i]) % dc;
    analogWrite(PINS[i], analogRead(pin_value); 
    print_pin(PINS[i], pin_value);
  }
}
