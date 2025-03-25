# VEX V5 Receiving Data from Arduino

This VEX V5 program receives **analog sensor data** from an Arduino displays the value on the VEX Brain screen.

## How It Works
1. **RS-485 Initialization**: (using UART TTL to RS-485 converter)
   - Sets up a **serial connection** on **PORT20** (for the Arduino).
   - Configures the **baud rate** to **115200 bps** to match the Arduino's transmission rate.
   - Please view the hardware section for any details on the physical setup

2. **Data Reception**:
   - Waits until **2 bytes** (16-bit integer) are available from the Arduino.
   - Reads the **high byte** and **low byte** of the transmitted value.
   - Combines the two bytes to reconstruct the **sensor value** (0-1023).

3. **Display**:
   - The received **sensor value** is displayed on the **VEX Brain screen**.

## Explanation
1. **BAUDRATE**: The serial communication speed is set to **115200 bps** to match the Arduino.
2. **vexGenericSerialEnable()**: Enables the generic RS-485 interface on **PORT20**.
3. **vexGenericSerialReceiveAvail()**: Checks if **2 bytes** of data are available.
4. **vexGenericSerialReadChar()**: Reads individual bytes from the RS-485 stream.
5. **(highByte << 8) | lowByte**: Combines two bytes to reconstruct the original **16-bit** sensor value.
6. **Brain.Screen.print()**: Displays the sensor value on the **VEX Brain screen**.

