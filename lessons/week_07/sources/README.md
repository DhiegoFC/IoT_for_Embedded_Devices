
# ESP32 connected to an Access Point with MQTT Broker

* Utilize the programs at ([Esp32_Mqtt](Esp32_Mqtt)) to publish MQTT messages from ESP32 to a specific MQTT broker topic ("topic/test").
* The ([ESP32 Sketch file](Esp32_Mqtt/Esp32_Mqtt.ino)) can be configured to adjust MQTT and WiFi settings, enabling communications to the MQTT Broker.
* Use ([Node-Red flow](Node_Red/node_red_mqtt.json)) to subscribe to "topic/test" and read MQTT messages sent by the ESP32
* Monitor the messages in Node-Red that are comming from the ESP32. 

