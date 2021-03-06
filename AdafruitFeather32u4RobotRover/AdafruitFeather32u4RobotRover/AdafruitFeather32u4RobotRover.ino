/*
   Copyright (c) 2018 William H. Beebe, Jr.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <Arduino.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>

#include "Utilities.h"

#include "Comms.h"
#include "Melody.h"
#include "Motor.h"

// Name your rover here.
//
String BROADCAST_NAME = "Adafruit Feather 32u4 Rover";

Comms comms;
DataFourFloats dff;
Motor motor;
Melody melody;

// -----------------------------------------------------------------------------
// Initializes all necessary hardware and prepares the robot for operations
// (this function is called automatically on startup)
// -----------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  delay(6000);

  Serial.println();
  Serial.println(F("Adafruit Bluefruit Robot Controller Example"));
  Serial.println(F("-------------------------------------------"));
  Serial.println(F("Use Adafruit Bluefruit LE Connect, then use"));
  Serial.println(F("Modules | Controller | Control Pad."));
  Serial.println();

  comms.setup(BROADCAST_NAME);
  motor.setup();
  melody.setup();
}

// -----------------------------------------------------------------------------
// Runs the application from here (this function is called automatically after
// setup is called).
// All of the available commands from the Controller module of the Adafruit app
// are handled here, with the notable exception of the Color Picker.
//
// The button commands are handled completely in doButtonCommand, while the rest
// of the commands simply print out what they recieve on the Serial Monitor.
// Thus, to see what they print, open Arduino's Serial Monitor window and then
// look at the output that prints out there.
// -----------------------------------------------------------------------------

void loop() {
  if (comms.readData()) {
    switch (comms.getCommandType()) {
      case BUTTON_CMD:
        //
        // The user has pressed a button on the screen. As long as the user's
        // finger is on the button (screen), no other button event is sent.
        //
        if (comms.buttonIsPressed()) {
          doButtonCommand(comms.getButtonValue());
        } else {
          //
          // The user has lifted their finger off the button (screen) sending
          // a matching event. Turn the motors off and stop all motion.
          //
          motor.fullStop();
        }
        break;

      case QUARTERNION_CMD:
        printFloatData("Quarternion", true);
        break;

      case ACCELEROMETER_CMD:
        printFloatData("Accelerometer", false);
        break;

      case GYRO_CMD:
        printFloatData("Gyro", false);
        break;

      case MAGNETOMETER_CMD:
        printFloatData("Magnetometer", false);
        break;

      case LOCATION_CMD:
        dff = comms.getFloats(false);
        Serial.println("Location");
        Serial.print("  Lat: ");
        Serial.println(dff.x);
        Serial.print(" Long: ");
        Serial.println(dff.y);
        Serial.print("  Alt: ");
        Serial.println(dff.z);
        Serial.println();
        break;
    }
  }
}

// -----------------------------------------------------------------------------
// All of the buttons on the Adafruit app's Control Pad are fully decoded here.
// The four numeric buttons are bound to four different tunes, while the arrow
// keys move the rover in their respective directions. For this implementation,
// please note that left and right are in relation to viewing the rover from
// above, with the small wheel at top indicating forward direction.
// -----------------------------------------------------------------------------

void doButtonCommand(BUTTON_COMMAND buttonCommand) {
  printHex(buttonCommand);
  switch (buttonCommand) {
    case BUTTON_1:
      melody.play(SuperMarioBrosMelody);
      break;

    case BUTTON_2:
      melody.play(PeerGyntMelody);
      break;

    case BUTTON_3:
      melody.play(SmokeMelody);
      break;

    case BUTTON_4:
      melody.play(NatalMelody);
      break;

    case MOVE_FORWARD:
      motor.forward();
      motor.accelerate();
      break;

    case MOVE_BACKWARD:
      motor.backward();
      motor.accelerate();
      break;

    case TURN_LEFT:
      motor.turnLeft();
      motor.accelerate();
      break;

    case TURN_RIGHT:
      motor.turnRight();
      motor.accelerate();
      break;
  }
}

// -----------------------------------------------------------------------------
// A convenience function for printing the data in DataFourFloats.
// If called with printW false, then only prints x, y, and z.
// If called with printW true, then prints x, y, z, and w.
// -----------------------------------------------------------------------------

void printFloatData(char *title, bool printW) {
  dff = comms.getFloats(printW);
  Serial.println(title);
  Serial.print(" X: ");
  printHex(dff.x);
  Serial.println(dff.x);
  Serial.print(" Y: ");
  printHex(dff.y);
  Serial.println(dff.y);
  Serial.print(" Z: ");
  printHex(dff.z);
  Serial.println(dff.z);

  if (printW) {
    Serial.print(" W: ");
    printHex(dff.w);
    Serial.println(dff.w);
  }

  Serial.println();
}
