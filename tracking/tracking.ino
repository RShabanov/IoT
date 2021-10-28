const int TRIG_PIN = 11;
const int ECHO_PIN = 10;
const int PIR_pin = 13; 
const int LIGHT_PIN = 8;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_pin, INPUT);
  Serial.begin(9600);
}

// 1st
void get_perfect_distance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration / 2. * 0.0343; // in cm
  Serial.print("Perfect distance: ");
  Serial.println(distance);
}

// 2nd
bool get_PIR_distance() {
  bool on = digitalRead(PIR_pin);

  // to detect that we have distance that we need
  if (on) {
    digitalWrite(LIGHT_PIN, HIGH);
  }
  else {
    digitalWrite(LIGHT_PIN, LOW);
  }
}

// 3rd
void get_IR_distance() {
  float volts = analogRead(A0)*0.0048828125;  // value from sensor * (5/1024)
  float distance = 13*pow(volts, -1); // worked out from datasheet graph
  delay(1000); // slow down serial port 

  Serial.print("Measured distance: ");
  Serial.println(distance);
}

void loop() {
  // 1st task
  // get_perfect_distance();

  // 2nd task
  // get_IR_distance();

  // 3rd task
  //  get_IR_distance();

  // 4th task
   if (!digitalRead(LASER_PIN)) {
     get_perfect_distance();
   }
}
