#include "ConnectionMqtt.h"

// WiFi and MQTT Settings
const char* ssid = "IoT_ES";
const char* password = "iot12345";
const char* mqttServer = "10.3.141.1";
const int mqttPort = 1883;
const char* mqttUser = "icts";
const char* mqttPassword = "icts12345";

ConnectionMqtt connectionMqtt(ssid, password, mqttServer, mqttPort, mqttUser, mqttPassword);

void setup() {
    Serial.begin(9600);
    connectionMqtt.connectWiFi();
    connectionMqtt.connectMQTT();
}

void loop() {
    if (connectionMqtt.isConnected()) {
        connectionMqtt.publish("test/topic", "Hello MQTT");
        delay(5000); // Wait 5 seconds
    } else {
        connectionMqtt.connectMQTT(); // Reconnect MQTT if the connection fails
    }
}
