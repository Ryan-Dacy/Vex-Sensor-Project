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

char sensorName[64] = "UNKNOWN";
bool nameReceived = false;
int receivedValue = 0;

void processSensorData() {
    char incomingChar;
    int index = 0;

    while (true) {
        int available = vexGenericSerialReceiveAvail(ArduinoMotor.index());

        if (!nameReceived && available > 0) {
            // Read the sensor name until newline
            while (vexGenericSerialReceiveAvail(ArduinoMotor.index()) > 0) {
                incomingChar = vexGenericSerialReadChar(ArduinoMotor.index());

                if (incomingChar == '\n' || index >= sizeof(sensorName) - 1) {
                    sensorName[index] = '\0'; // Null-terminate the string
                    nameReceived = true;
                    break;
                } else {
                    sensorName[index++] = incomingChar;
                }
            }
        } 
        else if (nameReceived && available >= 2) {
            // Read sensor value
            int highByte = vexGenericSerialReadChar(ArduinoMotor.index());
            int lowByte = vexGenericSerialReadChar(ArduinoMotor.index());
            receivedValue = (highByte << 8) | lowByte;

            // Display both name and value
            Brain.Screen.clearScreen();
            Brain.Screen.setCursor(1, 1);
            Brain.Screen.print("Sensor Type: %s", sensorName);
            Brain.Screen.newLine();
            Brain.Screen.print("Sensor Data: %d", receivedValue);
        }

        task::sleep(50);
    }
}

void driveRobot() {
    Drivetrain.setDriveVelocity(35, percent);
    while (true) {
        if (receivedValue < 135) {
            Drivetrain.drive(forward);
        } else {
            Drivetrain.stop();
            Drivetrain.driveFor(reverse, 100, inches);
            Drivetrain.stop();
        }
        task::sleep(50);
    }
}

int main() {
    vexcodeInit();
    vexGenericSerialEnable(ArduinoMotor.index(), 0);
    vexGenericSerialBaudrate(ArduinoMotor.index(), BAUDRATE);

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Starting threads...");

    thread sensorThread = thread(processSensorData);
    thread driveThread = thread(driveRobot);

    while (true) {
        task::sleep(100);
    }
}

