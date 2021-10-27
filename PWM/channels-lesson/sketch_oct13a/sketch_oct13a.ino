//struct 

int DIGITAL_PINS[] = { 0, 1, 2 };
int PWM_PINS[] = { 9, 10, 11 };

int LED_DELAYS[][3] = {
  { 10, 20, 30 },
  { 20, 40, 60 },
  { 50, 100, 150 },
};

void blink() {
  static int index_delay = 2;
  for (size_t i = 0; i < sizeof(DIGITAL_PINS) / sizeof(DIGITAL_PINS[0]); i++) {
    digitalWrite(DIGITAL_PINS[i], (millis() / LED_DELAYS[index_delay][i] % 2));
  }
//  index_delay = (index_delay + 1) % 3;
}

void light_PWM() {
  for (size_t i = 0; i < 3; i++) {
    analogWrite(PWM_PINS[i], 50 * (i + 1) );
  }
}

void setup() {
  for (auto& pin : DIGITAL_PINS) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  light_PWM();
  blink();

}
