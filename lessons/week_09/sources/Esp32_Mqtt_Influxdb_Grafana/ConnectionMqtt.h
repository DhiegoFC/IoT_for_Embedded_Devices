//#ifndef ConnectionMqtt_h
#define ConnectionMqtt_h

#include <WiFi.h>
#include <PubSubClient.h>

// WiFi and MQTT Settings
extern const char* ssid;
extern const char* password;
extern const char* mqttServer;
extern const int mqttPort;
extern const char* mqttUser;
extern const char* mqttPassword;

class ConnectionMqtt {
public:
    //ConnectionMqtt(const char* ssid, const char* password, const char* mqttServer, const int mqttPort);
    ConnectionMqtt(const char* ssid, const char* password, const char* mqttServer, const int mqttPort, const char* mqttUser, const char* mqttPassword);
    void connectWiFi();
    void connectMQTT();
    bool publish(const char* topic, const char* payload);
    bool isConnected();
    void setCallback(void (*callback)(char*, byte*, unsigned int));
    void loop();


private:
    const char* _ssid;
    const char* _password;
    const char* _mqttServer;
    int _mqttPort;
    const char* _mqttUser;
    const char* _mqttPassword;
    WiFiClient _espClient;
    PubSubClient _client;
};

//#endif
