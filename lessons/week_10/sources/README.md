# LoRaWAN ChirpStack Server Setup

- **Install ChirpStack**: Install ChirpStack on your computer. For Windows users, [Docker](https://www.chirpstack.io/docs/getting-started/docker.html) is recommended for the installation process.
- **Configure Server Components**: On the ChirpStack server, create a Gateway, Device Profile, and a LoRaWAN application. Ensure to configure your ChirpStack Gateway Bridge to operate on the AU915 frequency band, which is used in Brazil.
- **Gateway Configuration**: The professor will configure a LoRaWAN Gateway to forward packets to your ChirpStack server.
- **Device Connection**: The professor will provide the following LoRaWAN end devices for connection to your ChirpStack LoRaWAN server:
  - **Milesight Ambience Monitoring Sensor**: This device will be used to monitor air quality using the LoRaWAN AU915 frequency band. You can download its User Guide and Software Tool from [Milesight](https://www.milesight.com/iot/product/lorawan-sensor/am107).
  - **RAK3172 WisDuo LPWAN Module**: This module will demonstrate operation using the LoRaWAN AU915 frequency band with [AT Commands](https://docs.rakwireless.com/RUI3/Serial-Operating-Modes/AT-Command-Manual/#lorawan-joining-and-sending).
  - **RN2483 Microchip**: The professor will provide this device, which operates with the LoRaWAN EU868 frequency band using [AT Commands](https://ww1.microchip.com/downloads/en/DeviceDoc/40001784B.pdf).




