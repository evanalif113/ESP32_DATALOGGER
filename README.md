# ESP32 Data Logger with SHT31 Sensor, RTC, and microSD Card

This project demonstrates how to create a data logger using the ESP32 microcontroller, an SHT31 temperature and humidity sensor, a DS3231 Real-Time Clock (RTC) module, and a microSD card module. The data logger records temperature and humidity readings along with timestamps, saving the data to a microSD card for later analysis.

## Table of Contents

- [Features](#features)
- [Components Required](#components-required)
- [Circuit Diagram](#circuit-diagram)
- [Setup and Installation](#setup-and-installation)
- [How It Works](#how-it-works)
- [Code Overview](#code-overview)
- [Usage](#usage)
- [License](#license)

## Features

- **Temperature and Humidity Sensing:** Uses the SHT31 sensor to measure temperature and humidity.
- **Timestamping:** Utilizes the DS3231 RTC to provide accurate timestamps for each reading.
- **Data Logging:** Records data on a microSD card for easy retrieval and analysis.
- **Power Efficiency:** The ESP32 can be set to deep sleep mode between readings to conserve power.

## Components Required

- ESP32 Development Board
- SHT31 Temperature and Humidity Sensor
- DS3231 RTC Module
- microSD Card Module
- microSD Card (formatted as FAT32)
- Breadboard and Jumper Wires
- 10kΩ Pull-up resistors for I2C lines (optional, if needed)
- Relay module (if adding temperature-based control)

## Circuit Diagram

### Basic Connections:

- **ESP32 -> SHT31:**
  - 3.3V -> VCC
  - GND -> GND
  - GPIO 21 -> SDA
  - GPIO 22 -> SCL

- **ESP32 -> DS3231:**
  - 3.3V -> VCC
  - GND -> GND
  - GPIO 21 -> SDA
  - GPIO 22 -> SCL

- **ESP32 -> microSD Card Module:**
  - 3.3V -> VCC
  - GND -> GND
  - GPIO 5 -> CS
  - GPIO 18 -> SCK
  - GPIO 19 -> MISO
  - GPIO 23 -> MOSI

- **Optional: ESP32 -> Relay Module:**
  - 3.3V -> VCC
  - GND -> GND
  - GPIO (your choice) -> IN

## Setup and Installation

1. **Install PlatformIO or Arduino IDE:**
   - Ensure you have PlatformIO or Arduino IDE installed. PlatformIO is recommended for ease of library management.

2. **Install Required Libraries:**
   - Install the following libraries using the Library Manager:
     - `Adafruit SHT31`
     - `RTClib`
     - `SD`
     - `SPI`
     - `ArduinoJson` (if handling JSON data)

3. **Wiring:**
   - Follow the circuit diagram to connect the ESP32 with the SHT31, DS3231, and microSD card module.

4. **Code:**
   - Upload the provided code to your ESP32. Make sure to adjust the pin numbers and other settings according to your wiring.

## How It Works

The ESP32 reads temperature and humidity data from the SHT31 sensor. The DS3231 RTC provides accurate timestamps for each reading. The data, including the temperature, humidity, and timestamp, is then written to a file on the microSD card. The ESP32 can be set to enter deep sleep mode between readings to conserve power, making it ideal for battery-powered applications.

## Code Overview

The core of the code is structured as follows:

1. **Setup:**
   - Initialize the sensor, RTC, and microSD card module.
   - Set up the deep sleep timer.

2. **Main Loop:**
   - Read temperature and humidity from the SHT31 sensor.
   - Get the current timestamp from the DS3231 RTC.
   - Format the data and write it to the microSD card.
   - Enter deep sleep mode.

3. **Relay Control (Optional):**
   - If temperature exceeds a set threshold (e.g., 36°C), the relay is activated.

## Usage

1. **Insert the microSD card:**
   - Ensure the microSD card is inserted into the microSD card module and formatted as FAT32.

2. **Power the ESP32:**
   - Power the ESP32 using a USB cable or battery.

3. **Check Serial Monitor:**
   - Open the Serial Monitor at 115200 baud to see the logging status and any errors.

4. **Retrieve Data:**
   - Remove the microSD card after logging and insert it into a computer to view the logged data.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
