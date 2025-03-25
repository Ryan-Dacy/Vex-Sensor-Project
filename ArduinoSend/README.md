# Arduino Analog to UART Transmission

This Arduino program reads an analog voltage from **pin A2** and transmits the digital equivalent over UART (TX pin).

## How It Works
1. **Analog Reading**:
   - The Arduino reads the voltage on **pin A2** using `analogRead()`.
   - This value ranges from **0 to 1023**, where:
     - **0** corresponds to **0V**.
     - **1023** corresponds to **5V**.

2. **Data Transmission**:
   - The value is split into **two bytes** (a 16-bit integer).
   - The **high byte** and **low byte** are sent using `Serial.write()`.

## Code
```cpp
#define BAUDRATE 115200

const int sensorPin = A2;

void setup() {
    Serial.begin(BAUDRATE);
}

void loop() {
    int sensorValue = analogRead(sensorPin); // 0-1023

    // Send the value as two bytes (16-bit integer)
    Serial.write((sensorValue >> 8) & 0xFF); // High byte
    Serial.write(sensorValue & 0xFF);        // Low byte
}
```

## Explanation
1. **BAUDRATE**: The serial communication speed is set to **115200 bps**.
2. **analogRead(sensorPin)**: Reads the voltage from **A2** (0-5V range) and converts it to a **0-1023** value.
3. **Serial.write()**: Sends the 16-bit value as **two bytes**:
   - First, the **high byte** (most significant 8 bits).
   - Second, the **low byte** (least significant 8 bits).



