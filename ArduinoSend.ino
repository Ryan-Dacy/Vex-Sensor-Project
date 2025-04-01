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