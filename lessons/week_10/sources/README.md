## LoRaWAN ChirpStack Server Setup

**Objectives**:
- Install the LoRaWAN ChirpStack Server on your computer and create a LoRaWAN application.
- Configure the remote LoRaWAN ChirpStack Server and create a LoRaWAN application.
- Familiarize yourself with LoRaWAN end devices.
- Send LoRaWAN messages to both the local and the remote ChirpStack servers.

## Device Connection
The professor will provide the following LoRaWAN end devices for connection to both your local and remote ChirpStack servers:
- **Milesight Ambience Monitoring Sensor**: This sensor monitors air quality using the LoRaWAN AU915 frequency band. Download its User Guide and Software Tool from [Milesight](https://www.milesight.com/iot/product/lorawan-sensor/am107).
- **RAK3172 WisDuo LPWAN Module**: This module operates using the LoRaWAN AU915 frequency band. Learn more about its operation with [AT Commands](https://docs.rakwireless.com/RUI3/Serial-Operating-Modes/AT-Command-Manual/#lorawan-joining-and-sending).
- **RN2483 Microchip**: This device operates on the LoRaWAN EU868 frequency band. Familiarize yourself with its functionality through the [AT Commands Manual](https://ww1.microchip.com/downloads/en/DeviceDoc/40001784B.pdf).

## LoRaWAN Local ChirpStack Server Setup (AU915)

- **Install ChirpStack**: Install ChirpStack on your computer. For Windows users, [Docker](https://www.chirpstack.io/docs/getting-started/docker.html) is recommended.
- **Configure Docker for AU915 Messages**: If you are using ChirpStack on Windows, update your docker-compose by following [this guide](ChirpStack_AU915). Then, run `docker-compose up` to apply the new configuration. By default, ChirpStack is configured for EU868 messages.
- **Configure ChirpStack Server Components**: On the ChirpStack server, create a Gateway using the DEVUEI provided by your professor, a Device Profile for AU915 Frequency Band, a LoRaWAN application, and register devices within the application using the Device EUI also provided by your professor.
- **Gateway Configuration**: The professor will configure a LoRaWAN Gateway to forward packets to your ChirpStack server.

## LoRaWAN Remote ChirpStack Server Setup (AU915 and EU868)

- **Access the Remote ChirpStack Server**: Access the [remote LoRaWAN ChirpStack Server](http://186.217.146.38:8080/) hosted at UNESP/ICTS using the username: `students@unesp.br` and password: `students`.
- **Configure Remote Server Components**: On the remote ChirpStack server, create a LoRaWAN application and register devices within this application using the Device EUI provided by your professor.
- **Gateways**: Two LoRaWAN gateways are operating in the EU868 and AU915 frequency bands, forwarding messages to the remote ChirpStack server. The remote server is configured to receive messages from both gateways.
