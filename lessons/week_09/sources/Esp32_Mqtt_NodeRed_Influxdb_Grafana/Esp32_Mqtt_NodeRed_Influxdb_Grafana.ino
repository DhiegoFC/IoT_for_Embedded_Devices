#include "ConnectionMqtt.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

long duration; // sound wave travel time in microseconds measuared by HC-SR04 sensor

const int ledPin = 15; // Replace with the pin your LED is connected to
const int trigPin = 4; // Trig and Echo Pins from HC-SR04 sensor
const int echoPin = 2; // Trig and Echo Pins from HC-SR04 sensor

Adafruit_BME280 bme; // read temperature, pressure and humidity from here.

unsigned long lastTempMeasurement = 0; 
const long tempInterval = 60000; // Interval between temperature readings, e.g., 60 seconds

// Sensors variables
float distanceCm;
float humidity;
float pressure;
float temperature_esp32;
float temperature;

ConnectionMqtt connectionMqtt(ssid, password, mqttServer, mqttPort, mqttUser, mqttPassword);

/*
  Setup - Initial Configuration 
*/
void setup() {
  Serial.begin(9600);
  // Sets the trigPin as an Output and echoPin as an Input (HC-SR04 Sensor)
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);   
  // Start BM280 sensor
   bme.begin(0x76);
  // Initialize the LED's state to off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  // Start Wi-Fi and MQTT connection
  connectionMqtt.setCallback(ledControlCallback);  // Led Control Callback
  connectionMqtt.connectWiFi();
  connectionMqtt.connectMQTT();
}

/*
  Get distance sensor reading from HC-SR04 
*/
void getSensorHCSR04() {
    // Trigger sends a signal and reflects back to calculate the distance
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distanceCm = duration / 58.2;
}

/*
  Get sensors reading from BME280 
*/
void getSensorsBME280(){
    // Update the sensors reading on Arduino IoT Cloud
    temperature_esp32 = temperatureRead();;
    temperature = bme.readTemperature();
    pressure = bme.readPressure() / 100.0F;
    humidity = bme.readHumidity();
}

/*
  Return the sensors data in JSON format
*/
String createSensorDataJson() {
  String jsonOutput;  
  // Create a buffer for JSON document
  StaticJsonDocument<200> doc;
  // Adding the values to the JSON document
  doc["temperature_esp32"] = temperature_esp32;
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["pressure"] = pressure;
  doc["distance"] = distanceCm;
  // Create a stirng to store the JSON serialized output 
  serializeJson(doc, jsonOutput);
  return jsonOutput;
}

/*
  Callback to control the led state
*/
void ledControlCallback(char* topic, byte* payload, unsigned int length) {
    payload[length] = '\0';
    String message = String((char*)payload);
    if (message.equalsIgnoreCase("ON")) {
        digitalWrite(ledPin, HIGH);  // Turn the Led ON
    } else if (message.equalsIgnoreCase("OFF")) {
        digitalWrite(ledPin, LOW);  // Turn the Led OFF
    }
}

/*
  Main Loop
*/
void loop() { 
  unsigned long currentMillis = millis();

  // Check if it's time for another sensors reading 
  if (currentMillis - lastTempMeasurement >= tempInterval) {
    lastTempMeasurement = currentMillis;
    getSensorHCSR04();
    getSensorsBME280();
    String sensor_data = createSensorDataJson();
    connectionMqtt.publish("home/sensor_data", sensor_data.c_str());
  }

  if (!connectionMqtt.isConnected()) {
    connectionMqtt.connectMQTT();
  }
  connectionMqtt.loop();  // Important to keep the MQTT connection and process messages
}
