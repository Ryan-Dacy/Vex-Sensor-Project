//This is a very simple program that sends '23' to the vex brain
#define BAUDRATE 115200

void setup() {
    Serial.begin(BAUDRATE);  // baudrates on the arduino and vex brain need to be the same
}

void loop() {
    Serial.write(23);  //TX pin on the arduino
    delay(1000);  
}


