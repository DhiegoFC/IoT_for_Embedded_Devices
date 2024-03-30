// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "b4f69619-ba80-4a9b-ad3d-bb95f9795548";

const char SSID[]               = "SSID";    // Network SSID (name)
const char PASS[]               = "PASSWD";    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = "KEY";    // Secret device password

void onRedLedChange();

float distanceCm;
float humidity;
float pressure;
float temperature_esp32;
bool red_led;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(distanceCm, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(humidity, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(pressure, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(temperature_esp32, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(red_led, READWRITE, ON_CHANGE, onRedLedChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);