#include <PubSubClient.h>

PubSubClient mqtt_client(wifi_client);

void callback(char* topic, byte* payload, uint32_t len) {
  Serial.print(topic);

  for (auto i = 0; i < len; i++) {
    Serial.print(char(payload[i]));
  }

  Serial.println("-------------------------");
}

void MQTT_init() {
  mqtt_client.setServer(MQTT_BROKER, MQTT_PORT);
  mqtt_client.setCallback(callback);
  
  String client_id = "esp8266-shr-" + String(WiFi.macAddress());

  while (!mqtt_client.connected()) {
    if (mqtt_client.connect(client_id.c_str())) {
      Serial.println("MQTT connected with id (" + client_id + ")");
    }
    else {  
      Serial.println("MQTT failed");
    }
  }
}
