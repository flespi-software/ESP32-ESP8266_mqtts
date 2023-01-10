#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "credentials.h" // WIFI/MQTT credentials, certs

#if defined(ESP32) || defined(ESP8266)
WiFiClientSecure  wifiClient;
#endif

PubSubClient client(wifiClient);

void onMessage(char* topic, byte* message, unsigned int length) {
  Serial.print(topic);
  Serial.print(" : ");
  String tmp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    tmp += (char)message[i];
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Try to connect
    if (client.connect(MQTT_CLIENT, FLESPI_TOKEN, "")) {
      Serial.println("connected");
      // Subscribe to topic(s)
      client.subscribe(MQTT_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("retry again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Ready");
#if defined(ESP32)
  wifiClient.setCACert(root_ca);
#elif defined(ESP8266)
  wifiClient.setFingerprint(fingerprint);
#endif
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(">");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(onMessage);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(">");
  }
  client.loop();

  client.publish(MQTT_TOPIC, "Hello world!");
  delay(1000);
}
