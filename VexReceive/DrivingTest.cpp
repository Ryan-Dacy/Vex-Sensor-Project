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
motor leftMotorA = motor(PORT3, ratio18_1, true);
motor leftMotorB = motor(PORT5, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT12, ratio18_1, false);
motor rightMotorB = motor(PORT11, ratio18_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
inertial DrivetrainInertial = inertial(PORT10);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 319.19, 320, 40, mm, 1);

motor Motor17 = motor(PORT17, ratio18_1, false);

motor Motor18 = motor(PORT18, ratio18_1, false);

digital_out DigitalOutB = digital_out(Brain.ThreeWirePort.B);
controller Controller1 = controller(primary);


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

bool vexcode_initial_drivetrain_calibration_completed = false;
void calibrateDrivetrain() {
  wait(200, msec);
  Brain.Screen.print("Calibrating");
  Brain.Screen.newLine();
  Brain.Screen.print("Inertial");
  DrivetrainInertial.calibrate();
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  vexcode_initial_drivetrain_calibration_completed = true;
  // Clears the screen and returns the cursor to row 1, column 1.
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
}

void vexcodeInit() {

  // Calibrate the Drivetrain
  calibrateDrivetrain();

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

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

// Variable to store the light sensor value
int receivedValue = 0;

// Function to handle light sensor data
void processLightSensor() {
    while (true) {
        // Wait until at least 2 bytes are available
        if (vexGenericSerialReceiveAvail(ArduinoMotor.index()) >= 2) {
            // Read high byte and low byte
            int highByte = vexGenericSerialReadChar(ArduinoMotor.index());
            int lowByte = vexGenericSerialReadChar(ArduinoMotor.index());
            
            // Reconstruct the 16-bit value (0-1023)
            receivedValue = (highByte << 8) | lowByte;

            // Display the correct value (0-1023)
            Brain.Screen.clearScreen();
            Brain.Screen.setCursor(1, 1);
            Brain.Screen.print("Light Sensor: %d", receivedValue);
        }

        vex::task::sleep(20); // Small delay to prevent screen flicker
    }
}

// Function to handle drivetrain movements
void driveRobot() {
    Drivetrain.setDriveVelocity(35, percent);
    while (receivedValue < 135) {
        
            
            Drivetrain.drive(forward);
        

        vex::task::sleep(20); // Prevents rapid cycling of drivetrain logic
    }
    while (receivedValue >= 135) {
        
            Drivetrain.stop();
            Drivetrain.driveFor(reverse, 100, inches);
            Drivetrain.stop();
        

        vex::task::sleep(20); // Prevents rapid cycling of drivetrain logic
    }
}

int main() {
    vexcodeInit();
    vexGenericSerialEnable(ArduinoMotor.index(), 0);
    vexGenericSerialBaudrate(ArduinoMotor.index(), BAUDRATE);

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Starting threads...");

    // Create threads for the two tasks
    thread lightSensorThread = thread(processLightSensor);
    thread drivetrainThread = thread(driveRobot);

    // Keep the main program running (optional if no other logic is needed)
    while (true) {
        vex::task::sleep(100); // Keeps the program alive
    }

    return 0;
}
