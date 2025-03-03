# Vex-Sensor-Project
A custom-built light sensor for VEX robots using an Arduino Nano.

## Overview
This project implements a custom light sensor for VEX robots using an **Arduino Nano** and an **RS-485 communication module**. The sensor reads light intensity and transmits the data to the **VEX Brain** using a **TTL to RS-485 converter**.

## Hardware Components
- **Arduino Nano** – Reads light sensor data and transmits via RS-485.
- **VEX Brain** – Receives the light data.
- **Light Sensor** – Detects ambient light intensity.
- **TTL to RS-485 Converter (MAX485 Module)** – Converts TTL signals from Arduino to RS-485.
- **12V to 5V Step-Down Converter** – Powers the Arduino from the VEX system.

## How It Works
1. The **Arduino Nano** reads data from the light sensor.
2. The data is transmitted via **RS-485** using the **TTL to RS-485 converter**.
3. The **VEX Brain** receives the RS-485 signal and processes the light data.

## Wiring Diagram
- **Arduino Nano TX → TX MAX485
- **Arduino Nano RX ← RX on MAX485  
- **MAX485 A & B → VEX Brain RS-485 Input**  
- **Power**: The Arduino Nano is powered using a **12V to 5V step-down converter** from the VEX system.

## Software
- The Arduino will continuously read light sensor values and send them over RS-485.
- The VEX Brain will receive the transmitted data and process it accordingly.

## Future Improvements
- Implement data validation and error checking.
- Add support for additional sensors.
- Optimize communication efficiency.


