#include "ConnectionMqtt.h"

ConnectionMqtt::ConnectionMqtt(const char* ssid, const char* password, const char* mqttServer, const int mqttPort, const char* mqttUser, const char* mqttPassword)
    : _ssid(ssid), _password(password), _mqttServer(mqttServer), _mqttPort(mqttPort), _mqttUser(mqttUser), _mqttPassword(mqttPassword), _client(_espClient) {
    _client.setServer(_mqttServer, _mqttPort);
}

void ConnectionMqtt::connectWiFi() {
    Serial.print("Connecting to ");
    Serial.print(_ssid);
    Serial.println(" ...");

    WiFi.begin(_ssid, _password);

    while (WiFi.status() != WL_CONNECTED) {
        //delay(500);
        Serial.print("WiFi Connection to ");
        Serial.print(_ssid);
        Serial.println(" FAILED!!!");
        Serial.print("Trying again Connection to Wi-Fi ");
        Serial.print(_ssid);
        Serial.println(" in 5 seconds...");
        delay(5000);
    }

    Serial.print("Connected to Wi-Fi ");
    Serial.print(_ssid);
    Serial.println("!!!");
}

void ConnectionMqtt::connectMQTT() {
    while (!_client.connected()) {
        Serial.print("Connecting to MQTT Broker ");
        Serial.print(_mqttServer);
        Serial.println(" ...");

        if (_client.connect("ESP32Client",  _mqttUser, _mqttPassword)) {
            Serial.print("Connected to MQTT Broker ");
            Serial.print(_mqttServer);
            Serial.println("!!!");
        } else {
            if (WiFi.status() == WL_CONNECTED){
              Serial.print("Failed, rc=");
              Serial.print(_client.state());
              Serial.println("");
              Serial.print(" Trying again Connection to MQTT Broker ");
              Serial.print(_mqttServer);
              Serial.println(" in 5 seconds...");
              delay(5000);
            }
            else{
              Serial.println("MQTT Broker disconnected due to no Wi-Fi connectivity...");
              ConnectionMqtt::connectWiFi();
            }
        }
    }
}

bool ConnectionMqtt::publish(const char* topic, const char* payload) {
    if (!_client.connected()) {
        connectMQTT();
    }
    return _client.publish(topic, payload);
}

bool ConnectionMqtt::isConnected() {
    return _client.connected();
}
