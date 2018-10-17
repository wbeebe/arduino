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

#ifndef COMMS_H
#define COMMS_H

#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>

#include "BluefruitConfig.h"

// ----------------------------------------------------------------------------------------------
// Taken from the Adafruit app's information help screen.
// All data is raw. All numbers are four byte floats and little endian.
// Quaternion data is the attitude of the smartphone and is derived from accelerometer, gyro, and
// magnetometer readings.
//
enum COMMAND_TYPE {
  START_CMD =         '!',    // The very first character of ever command packet.
  BUTTON_CMD =        'B',    // followed by button ID and if pressed ('1') or released ('0')
  BUTTON_PRESSED =    '1',
  QUARTERNION_CMD =   'Q',    // followed by x, y, z and w, all floats.
  ACCELEROMETER_CMD = 'A',    // followed by x, y, and z, all floats.
  GYRO_CMD =          'G',    // followed by x, y, and z, all floats.
  MAGNETOMETER_CMD =  'M',    // followed by x, y, and z, all floats.
  LOCATION_CMD =      'L'     // followed by latitude, longitude, and altitude, all floats.
};

enum BUTTON_COMMAND {
  // Generic keypad button values.
  //
  BUTTON_1 = '1',
  BUTTON_2 = '2',
  BUTTON_3 = '3',
  BUTTON_4 = '4',

  // Movement control button values.
  //
  MOVE_FORWARD =  '5',
  MOVE_BACKWARD = '6',
  TURN_LEFT =     '7',
  TURN_RIGHT =    '8'
};

// Many of the commands contain floats, either three in the packet, or four.
// This structure allows all those command's float data to be reconstructed from
// serialized byte data back into their respective float values.
//
// For all commands that only have three floats, the fourth (w) is set to zero.
//
struct DataFourFloats {
  float x;
  float y;
  float z;
  float w;
};

// ----------------------------------------------------------------------------------------------
// Size of the read buffer for incoming packets
//
#define MAX_PACKET_BUFSIZE  20

// ----------------------------------------------------------------------------------------------
// A specialized print buffer.
//
#define MAX_BUFSIZE 60

// ----------------------------------------------------------------------------------------------

class Comms {
  private:

    // Buffer to hold incoming characters. Make the buffer one byte larger than
    // MAX_PACKET_BUFSIZE so that no matter what, you don't overrun the buffer
    // IFF you're checking that you only fill up to MAX_PACKET_BUFSIZE.
    //
    uint8_t packetBuffer[MAX_PACKET_BUFSIZE + 1];

    Adafruit_BluefruitLE_SPI *ble;
    char broadcastBuffer[MAX_BUFSIZE];
    DataFourFloats dff;

  public:
    Comms();

    // Call from top-level setup with the device's string name.
    // This is your rover's identifying name.
    // This value will be displayed on the Adafruit Bluefruit
    // LE Connect app on the app's front page.
    //
    void setup(String &);

    // Raw read of any data sent across Bluetooth.
    // Returns > 0 if data is read, 0 if no data read.
    //
    uint8_t readData();

    // Get the command type.
    // Call this after a readData() returns a value > 0.
    //
    COMMAND_TYPE getCommandType();

    // Returns true if a button was pressed down, false if released.
    // Call after call to isButton();ghopł                          ````````````````````````````````````````
    //
    bool buttonIsPressed();

    // Returns the value of the button if a button was pressed.
    // Call after isButton, and if you're only interested in if it was
    // pressed, after isPressed.
    //
    char getButtonValue();

    // The following call returns either three float values in x,y, and z
    // of DataFourFloats if getFourthFloat is false,
    // or else four float values in x, y, z, and w if getFourthFloat is true.
    //
    DataFourFloats& getFloats(bool getFourthFloat);
};

#endif
