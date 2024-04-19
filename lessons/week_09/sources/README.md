# ESP32 with Embedded Sensors Connected to a Linux Virtual Machine Featuring Node-Red, InfluxDB and Grafana

* Assemble the sensors to the ESP32. You can read [this guidance](Esp32_NodeRed_Influxdb_Grafana/ReadMe.adoc) to assembly the beardboard.
* Use the [provided ESP32 code](Esp32_NodeRed_Influxdb_Grafana/) to connect ESP32 to the provided Wi-Fi AP embedded with MQTT broker.
* Create a Linux Virtual Machine in VirtualBox, configure one of its network interface as bridge in order to receive the IP from the PC's network.
* Install Node-Red, InfluxDB and Grafana in your Linux VM.
* Create the sensor_data database on InfluxDB.
* Use the [provided Node-Red Flows](Node_Red/sensor_and_led_flows.json) to receive MQTT messages from ESP32 to store the sensor measurements on database, and also to control the LED from Node-Red dashboard. Check figure below.

<img src="../../../images/Node_Red_ui.jpg" width="450" height="400">
* Connect Grafana to the sensor_data database and visualize each sensor measurements on the screen (temperature, tempeture_esp32, humidity, pressure and distance). See the figure below.

![Grafana dashboard](../../../images/grafana_dashboard.png)


**Note**: For guidance on integrating the ESP32 to an Linux Virtual Machine server Featuring Node-Red, InfluxDB, and Grafana, consider watching this instructional video on <a href="https://www.youtube.com/watch?v=_DO2wHI6JWQ"> <img src="../../../images/youtube.jpg" alt="youtube" width="80" height="17" /> </a>


