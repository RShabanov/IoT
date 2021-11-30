#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "MQTT.h"

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  WIFI_init(MODE_AP);

  server_init();

  MQTT_init();  
  mqtt_client.publish((BASE_MQTT_TOPIC + String("/state")).c_str(), "Hello");
  mqtt_client.subscribe((BASE_MQTT_TOPIC + String("/command")).c_str());
}

void loop() {
  server.handleClient();
  mqtt_client.loop();
}
