int trig_pin = 11;
int echo_pin = 10;
int PIR_pin = 13; 
int LIGHT_PIN = 8;
int LASER_PIN = 9;
//int IR_PIN = 9;
long duration;


void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(PIR_pin, INPUT);
  Serial.begin(9600);
}

void get_perfect_distance() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  float distance = duration / 2. * 0.0343; // in cm
  Serial.print("Perfect distance: ");
  Serial.println(distance);
}

// 2nd
bool get_PIR_distance() {
  // CHANGE PIN - CAUSE IT IS FOR LASER
  // BUT CODE THE SAME
  bool on = digitalRead(PIR_pin);
//  Serial.println(on)[;

  return !on;

  // to detect that we have distance that we need
  if (on) {
    digitalWrite(LIGHT_PIN, HIGH);
  }
  else {
    digitalWrite(LIGHT_PIN, LOW);
  }
}

void get_IR_distance() {
  float volts = analogRead(A0)*0.0048828125;  // value from sensor * (5/1024)
  float distance = 13*pow(volts, -1); // worked out from datasheet graph
  delay(1000); // slow down serial port 

      Serial.print("Measured distance: ");
    Serial.println(distance);   // print the distance 
}

// opening/closing
void detect_opening() {
  bool open_door = digitalRead(LASER_PIN);
  if (open_door) {
    Serial.println("Door is open");
  }
  else {
    Serial.println("Door is closed");
  }
}

void loop() {
  // 1st
//  get_perfect_distance();
// 4th
//  if (get_PIR_distance()) {
//    get_perfect_distance();
//  }
//3rd
//  get_IR_distance();
  detect_opening();
  
}
