int trig_pin = 11;
int echo_pin = 10;
long duration;


void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  float distance = duration / 2. * 0.0343; // in cm
  Serial.println(distance);
}
