# LoRaWAN ChirpStack Server Integration

- ChirpStack Server can be integrated with various servers and applications, including InfluxDB, MQTT, HTTP, and more.
- In this tutorial, you will utilize the internal ChirpStack MQTT Broker to receive LoRaWAN uplink messages.
- To listen to the ChirpStack MQTT Broker, use Node-RED and subscribe to the specific topic: "application/applicationID/device/deveui/event/up".
- Node-RED is an excellent software tool for managing data flows and processing data. LoRaWAN devices transmit raw data to minimize power consumption; hence, data processing is managed server-side.
- Ensure the ChirpStack MQTT Broker is configured to allow remote connections if you are using Node-RED on a different PC.
- For additional information on ChirpStack MQTT integration, you can read more [here](https://www.chirpstack.io/docs/chirpstack/integrations/mqtt.html).


