enum class Direction : uint8_t {
  N = A0,
  E = A1,
  S = A2,
  W = A3,
};

void print_direction(Direction dir) {
  switch (dir) {
    case Direction::N:
      Serial.print("North: ");
      break;
    case Direction::E:
      Serial.print("East: ");
      break;
    case Direction::S:
      Serial.print("South: ");
      break;
    case Direction::W:
      Serial.print("West: ");
      break;
  };

  Serial.println(analogRead((uint8_t)dir));
}

int direction2look() {
  print_direction(Direction::N);
  print_direction(Direction::E);
  print_direction(Direction::S);
  print_direction(Direction::W);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
//  Serial.print("Sensor data: ");
//  Serial.println(analogRead(A0));
//  Serial.println("---------------------------------");
  
  direction2look();
}
