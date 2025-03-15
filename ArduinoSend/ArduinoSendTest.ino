#define BIT_LED 3  // White LED for bits
#define CHAR_LED 4 // Yellow LED for letter end

void setup() {
    pinMode(BIT_LED, OUTPUT);
    pinMode(CHAR_LED, OUTPUT);
    Serial.begin(9600);  // Start Serial Monitor

    sendBinary('H');  // Send 'H' (01001000)
    delay(2000);       // Pause before next letter
    sendBinary('i');   // Send 'i' (01101001)

    Serial.println("Transmission complete.");
}

void loop() {
    // Nothing happens after the message is sent
}

void sendBinary(char c) {
    Serial.print("Sending: ");
    Serial.println(c);

    Serial.write(c); //Send the bits over the TX pin

    // Read bits from MSB (bit 7) to LSB (bit 0)
    for (int i = 7; i >= 0; i--) {
        bool bit = (c >> i) & 1; // Extract bit
        Serial.print(bit);  // Print the bit value to Serial Monitor
        Serial.print(" ");

        // Turn LED on if bit is 1, off if bit is 0
        digitalWrite(BIT_LED, bit);
        delay(500);  // Ensures the LED is visible for this bit

        // Turn off the LED before moving to the next bit (ensures clear blinks)
        digitalWrite(BIT_LED, LOW);
        delay(500);  // Small gap before next bit
    }

    Serial.println(); // New line for readability

    // Blink yellow LED to indicate letter completion
    Serial.println("Yellow LED Blink");
    digitalWrite(CHAR_LED, HIGH);
    delay(1000);  // Ensures it is clearly visible
    digitalWrite(CHAR_LED, LOW);
}
