# ESP32 Water Turbidity Monitoring Project

This project involves using an ESP32 to monitor water turbidity levels through a turbidity sensor. The ESP32 reads the turbidity levels and sends this data to a server via HTTP requests. It's designed to work in environments where monitoring water quality is crucial, such as in aquaculture, water treatment facilities, and environmental studies.

## Hardware Requirements

- ESP32 Development Board
- Turbidity Sensor
- Jumper Wires

## Software Requirements

- Arduino IDE
- ESP32 Board Support installed in Arduino IDE
- WiFi Library for ESP32
- HTTPClient Library for ESP32

## Setup Instructions

### Hardware Setup

1. Connect the turbidity sensor to the ESP32 ADC pin (e.g., GPIO 34).
2. Ensure the ESP32 is powered correctly.

### Software Setup

1. Install the Arduino IDE and add support for the ESP32 board.
2. Install the `WiFi` and `HTTPClient` libraries using the Library Manager in the Arduino IDE.
3. Configure your WiFi credentials in the code.

## Code Overview

The code performs the following functions:

1. Initializes serial communication and connects to the specified WiFi network.
2. Once connected, it prints the ESP32's IP address on the network.
3. Periodically reads the turbidity sensor value.
4. Sends the sensor data to a server via an HTTP request.
5. Waits for 3 seconds before repeating the sensor reading and data sending process.

## WiFi Configuration

Replace the `ssid` and `password` variables in the code with your WiFi network's SSID and password.

```cpp
const char* ssid = "Your_SSID_Here";
const char* password = "Your_Password_Here";