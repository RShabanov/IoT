const int LASER_INT = 9;

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

void setup() {
  Serial.begin(9600);
}

void loop() {
  detect_opening(); 
}