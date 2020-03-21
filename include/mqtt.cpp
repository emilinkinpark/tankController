
#include <WiFi.h>
extern "C" {
	#include "freertos/FreeRTOS.h"
	#include "freertos/timers.h"
}
#include <AsyncMqttClient.h>

#define mySSID "GloryAgro"
#define myPASSWORD "Gloryart1!1"

#define MQTT_HOST IPAddress(192, 168, 0, 20)
#define MQTT_PORT 1883


#define RELAY_PIN 7

#define MQTT_RELAY1_TOPIC     "LAB/LIGHT/MAIN/SWITCH"
#define MQTT_RELAY2_TOPIC     "LAB/LIGHT/BENCH"
#define MQTT_FEEDBACK1_TOPIC  "LAB/LIGHT/MAIN/FEEDBACK"
#define MQTT_LASTWILL_TOPIC   "LAB/LIGHT/lastwill"


AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;



void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void WiFiEvent(WiFiEvent_t event) {
    Serial.printf("[WiFi-event] event: %d\n", event);
    switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        connectToMqtt();
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("WiFi lost connection");
        xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
		xTimerStart(wifiReconnectTimer, 0);
        break;
    }
}
void setRelay(String command) {
  if (command == "ON") digitalWrite(RELAY_PIN, HIGH);
  else digitalWrite(RELAY_PIN, LOW);
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("** Connected to the broker **");

  mqttClient.subscribe(MQTT_RELAY1_TOPIC, 1);

  Serial.print("Subscribing : ");
  Serial.println(MQTT_RELAY1_TOPIC);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("** Disconnected from the broker **");
  Serial.println("Reconnecting to MQTT...");
  mqttClient.connect();
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.print("** Subscribe acknowledged **");
  Serial.print(" packetId: ");
  Serial.print(packetId);
  Serial.print(" qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("** Unsubscribe acknowledged **");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {

  Serial.println("** Message received **");
  Serial.print("  topic: ");
  Serial.print(topic);
  Serial.print("  feedbackTopic: ");
  Serial.print(MQTT_RELAY1_TOPIC);
  Serial.print("  qos: ");
  Serial.print(properties.qos);
  Serial.print("  dup: ");
  Serial.print(properties.dup);
  Serial.print("  retain: ");
  Serial.print(properties.retain);
  Serial.print("  len: ");
  Serial.print(len);
  Serial.print("  index: ");
  Serial.print(index);
  Serial.print("  payload: ");
  Serial.println(payload);

  if (strcmp(topic, MQTT_RELAY1_TOPIC) == 0)  {
    setRelay(payload);
    mqttClient.publish(MQTT_FEEDBACK1_TOPIC, 1, false, payload);
    Serial.println("Publishing Feedback");
  }
}

void onMqttPublish(uint16_t packetId) {
  Serial.print("** Published");
  Serial.print("  packetId: ");
  Serial.print(packetId);
  Serial.print("\n\n");
}

void mqttsetup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Start");

  // Relay PIN
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  WiFi.persistent(false);

  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(mySSID, myPASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" OK");

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  // mqttClient.onSubscribe(onMqttSubscribe);
  //  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(IPAddress(192, 168, 0, 201), 1883);
  mqttClient.setKeepAlive(5).setCleanSession(false).setWill(MQTT_LASTWILL_TOPIC, 2, true, "my wife will get all my money").setCredentials("username", "password").setClientId("m");
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}
