#include <Servo.h>

enum class Direction : uint8_t {
  N = A0,
  E = A1,
  S = A2,
  W = A3,
};

constexpr uint8_t SERVO_PIN = 9;
Servo servo;
int angle = 0;

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
  servo.attach(SERVO_PIN);
}

void loop() {
//  direction2look();
//  delay(1000);

  auto n = analogRead((uint8_t)Direction::N),
    w = analogRead((uint8_t)Direction::W),
    e = analogRead((uint8_t)Direction::E),
    s = analogRead((uint8_t)Direction::S);

     /*
   * if Direction::N => 0*
   * if Direction::E => 90*
   * if Direction::S => 135*
   * if Direction::W => 180*
   */

  auto c = n;
  auto angle = 0;
  Direction dir2look = Direction::N;
  if (c < w) {
    dir2look = Direction::W;
    c = w;
    angle = 180;
  }
  if (c < e) {
    dir2look = Direction::E;
    c = e;
    angle = 90;
  }
  if (c < s) {
    dir2look = Direction::S;
    c = s;
    angle = 135;
  }

  Serial.print("Angle: ");
  Serial.println(angle);
  
  servo.write(angle);
  delay(500);
}
