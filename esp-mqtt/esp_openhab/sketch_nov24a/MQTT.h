#include <PubSubClient.h>

PubSubClient mqtt_client(wifi_client);

void handle_command(byte* payload, uint32_t len);

void callback(char* topic, byte* payload, uint32_t len) {
  Serial.println();
  Serial.print("Topic: ");
  Serial.print(topic);
  Serial.println();

  if ((BASE_MQTT_TOPIC + String("/command")) == String(topic)) {
    handle_command(payload, len);
  }

  Serial.print("Received data: ");
  
  for (auto i = 0; i < len; i++) {
    Serial.print(char(payload[i]));
  }
  Serial.println();
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

  
void handle_command(byte* payload, uint32_t len) {
  char cmd[len + 1] {'\0'};
  for (auto i = 0; i < len; i++) {
    cmd[i] = char(payload[i]);
  }

  Serial.print("From handle_command: ");
  Serial.println(cmd);
  
  if (strcmp(cmd, "open") == 0) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (strcmp(cmd, "closed") == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
