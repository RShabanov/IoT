#include <FastLED.h>

const int DATA_PIN = 2;
const int CLOCK_PI = 3;
const uint8_t NUM_LEDS = 15;

CRGB leds[NUM_LEDS];

bool get_leds();

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {
  bool state = get_leds();
  if (state) {
    FastLED.show();
    state = 0;
  }
}

bool get_leds() {
  uint8_t i = 0;
  while (Serial.available() > 2) {
    if (i == 0) {
      delay(100);
    }
    
    if (i == NUM_LEDS - 1) {
      break;
    }
    uint8_t r = Serial.read();
    uint8_t g = Serial.read();
    uint8_t b = Serial.read();

    leds[i++] = CRGB(r, g, b);
  }

  return i != 0;  
}
