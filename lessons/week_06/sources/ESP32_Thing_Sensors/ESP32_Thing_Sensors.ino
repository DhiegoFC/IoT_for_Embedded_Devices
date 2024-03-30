/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/156a10f3-4c82-40c0-8b7a-00183645fbf3 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float distanceCm;
  float humidity;
  float pressure;
  float temperature_esp32;
  bool red_led;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

const int ledPin = 15; // Replace with the pin your LED is connected to
const int trigPin = 4; // Trig and Echo Pins from HC-SR04 sensor
const int echoPin = 2; // Trig and Echo Pins from HC-SR04 sensor

unsigned long lastTempMeasurement = 0; 
const long tempInterval = 1000; // Interval between temperature readings, e.g., 1 seconds

Adafruit_BME280 bme; // read temperature, pressure and humidity from here.

long duration; // sound wave travel time in microseconds measuared by HC-SR04 sensor
//float distanceCm; // distance calculated in centimeters


void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();
  
  // Initialize the LED's state to off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Sets the trigPin as an Output and echoPin as an Input (HC-SR04 Sensor)
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  
  // Start BM280 sensor
  bme.begin(0x76);

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
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
    // Update the sensors reading on Arduino IoT Cloud
    distanceCm = duration / 58.2;
    String disp = String(distanceCm);
    Serial.print(disp);
    Serial.println(" cm");
}

/*
  Get sensors reading from BME280 
*/
void getSensorsBME280(){ 
    
    // Update the sensors reading on Arduino IoT Cloud
    temperature_esp32 = temperatureRead();;
    //temperature = bme.readTemperature();
    pressure = bme.readPressure() / 100.0F;
    humidity = bme.readHumidity();
}

void loop() {
  ArduinoCloud.update();
  
  unsigned long currentMillis = millis();
    
  // Check if it's time for another sensors reading 
  if (currentMillis - lastTempMeasurement >= tempInterval) {
    lastTempMeasurement = currentMillis;
    //getSensorHCSR04();
    getSensorsBME280();
    // Trigger sends a signal and reflects back to calculate the distance
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    // Update the sensors reading on Arduino IoT Cloud
    distanceCm = duration / 58.2;
    String disp = String(distanceCm);
    Serial.print(disp);
    Serial.println(" cm");
  }  
}

/*
  Since RedLed is READ_WRITE variable, onRedLedChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onRedLedChange()  {
  // Update the LED state based on the value of ledState
  digitalWrite(ledPin, red_led ? HIGH : LOW);
}










