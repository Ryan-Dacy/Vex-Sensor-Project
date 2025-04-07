#define BAUDRATE 115200

const int sensorPin = A2;
const char* sensorName = "LIGHT SENSOR";  // Change this to any sensor name you want
bool nameSent = false;

void setup() {
  Serial.begin(BAUDRATE);
}

void loop() {
  int sensorValue = analogRead(sensorPin); // 0-1023

  if (!nameSent) {
    // Send sensor name followed by newline
    Serial.println(sensorName);
    nameSent = true;
  }

  // Send sensor value as 2 bytes (16-bit integer)
  Serial.write((sensorValue >> 8) & 0xFF); // High byte
  Serial.write(sensorValue & 0xFF);        // Low byte

  delay(200);  // Delay to avoid spamming
}
