# LED Binary Transmission Test

## Overview
This Arduino program was created to **test whether the Arduino is successfully transmitting data**. It sends characters in binary format via the serial port and blinks LEDs based on the transmitted bits. The LEDs provide a **visual confirmation** that the Arduino is correctly sending data.

## How It Works
1. The **white LED (BIT_LED, pin 3)** blinks when a `1` bit is transmitted.
2. The **yellow LED (CHAR_LED, pin 4)** blinks when a full character has been transmitted.
3. The program sends two characters (`H` and `i`) and then stops.
4. Each character is sent **bit by bit**, from the **most significant bit (MSB) to the least significant bit (LSB)**.
5. The **Serial Monitor** displays the transmission process.

## How to Verify Transmission
- The **white LED only turns on** when a `1` bit is sent. If the LED blinks in sync with the expected `1` bits, it confirms that the Arduino is transmitting data correctly.
- The **yellow LED blinks** at the end of each full character, indicating that all 8 bits of the character have been processed.
- If the LEDs do not blink as expected, it suggests that data is not being transmitted correctly or that the transmission is being interrupted.
- The **Serial Monitor output** can be checked alongside the LED blinks to confirm the transmission sequence.

## Hardware Requirements
- **Arduino Board** (Arduino Nano)
- **White LED** (Bit Indicator, connected to pin 3)
- **Yellow LED** (Character Completion Indicator, connected to pin 4)
- **Resistors** (e.g., 330Ω) for LEDs
- **Wires & Breadboard**

## Code Breakdown
### `setup()`
- Configures **BIT_LED (pin 3)** and **CHAR_LED (pin 4)** as outputs.
- Initializes serial communication at **9600 baud**.
- Calls `sendBinary()` to transmit 'H' and 'i'.

### `sendBinary(char c)`
- Prints the character being sent.
- Sends the character over **Serial TX**.
- Extracts **each bit** from the character and:
  - **Turns on the white LED** for `1`, **turns it off** for `0`.
  - **Pauses (500ms)** after each bit for visibility.
- Blinks the **yellow LED** for **1 second** after each full character is transmitted.

## Expected Output: In this example 'Hi' is transmitted
### Serial Monitor:
```
Sending: H
0 1 0 0 1 0 0 0 
Yellow LED Blink (indicating H was sent)
Sending: i
0 1 1 0 1 0 0 1 
Yellow LED Blink (indicating i was sent)
Transmission complete.
```
### LED Behavior:
- **White LED blinks** corresponding to each `1` bit. (the Highs)
- **Yellow LED blinks** after each full letter. (To indicate moving onto the next character)

## Future Improvements
-   Transmit light sensor data
-   Configure the Vex brain to properly recieve data

