#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.



// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"
using namespace vex;

#define BAUDRATE 115200
motor ArduinoMotor = motor(PORT20, ratio18_1, false);

int main() {
    vexcodeInit();
    vexGenericSerialEnable(ArduinoMotor.index(), 0);
    vexGenericSerialBaudrate(ArduinoMotor.index(), BAUDRATE);

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Waiting for data...");

    while (true) {
        // Wait until at least 2 bytes are available
        if (vexGenericSerialReceiveAvail(ArduinoMotor.index()) >= 2) {
            // Read high byte and low byte
            int highByte = vexGenericSerialReadChar(ArduinoMotor.index());
            int lowByte = vexGenericSerialReadChar(ArduinoMotor.index());
            
            // Reconstruct the 16-bit value (0-1023)
            int receivedValue = (highByte << 8) | lowByte;

            // Display the correct value (0-1023)
            Brain.Screen.clearScreen();
            Brain.Screen.setCursor(1, 1);
            Brain.Screen.print("Light Sensor: %d", receivedValue);
        }

        vex::task::sleep(20); // Small delay to prevent screen flicker
    }
}