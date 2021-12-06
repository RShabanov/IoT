#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "MQTT.h"

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  WIFI_init(MODE_AP);

  server_init();

  MQTT_init();  
  mqtt_client.publish((BASE_MQTT_TOPIC + String("/state")).c_str(), "off");
  mqtt_client.subscribe((BASE_MQTT_TOPIC + String("/command")).c_str());
  
}

void loop() {
  server.handleClient();
  mqtt_client.loop();

  bool led_state = analogRead(A0) == 1024;
  mqtt_client.publish((BASE_MQTT_TOPIC + String("/state")).c_str(), String(led_state ? "off" : "on").c_str());
}
