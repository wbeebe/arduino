/*
 * Copyright (c) 2018 William H. Beebe, Jr.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * This uses some example code for the nRF51822 based Adafuit Bluefruit LE modules
 * provided by Adafruit.
 * 
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 * 
 * Some portions use MIT license, check LICENSE for more information
 * All text above, and the splash screen below must be included in
 * any redistribution
 */

#include "Comms.h"

// ----------------------------------------------------------------------------------------------

Comms::Comms() {
}

// ----------------------------------------------------------------------------------------------

void Comms::setup(String &deviceName) {
    ble = new Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

    Serial.print(F("Initialising the Bluefruit LE module: "));

    if (not ble->begin(VERBOSE_MODE)) {
        error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
    }

    Serial.println( F("OK!") );

    // Perform a factory reset to make sure everything is in a known state
    //
    Serial.println(F("Performing a factory reset: "));
    if (not ble->factoryReset() ) {
        error(F("Couldn't factory reset"));
    }

    // Convert the name change command to a char array
    //
    String BROADCAST_CMD = String("AT+GAPDEVNAME=" + deviceName);
    BROADCAST_CMD.toCharArray(broadcastBuffer, MAX_BUFSIZE);

    // Change the broadcast device name here!
    //
    if(ble->sendCommandCheckOK(broadcastBuffer)) {
        Serial.println("name changed");
    }

    delay(250);

    // Reset to take effect
    //
    if(ble->sendCommandCheckOK("ATZ")) {
        Serial.println("resetting");
    }

    delay(250);

    // Confirm name change
    //
    ble->sendCommandCheckOK("AT+GAPDEVNAME");

    // Disable command echo from Bluefruit
    //
    ble->echo(false);

    Serial.println("Requesting Bluefruit info:");

    ble->info();

    ble->verbose(false);  // debug info is a little annoying after this point!

    // Wait for connection
    //
    while (not ble->isConnected()) {
        delay(500);
    }

    Serial.println(F("*****************"));

    // Set Bluefruit to DATA mode
    //
    Serial.println(F("Switching to DATA mode!"));
    ble->setMode(BLUEFRUIT_MODE_DATA);

    Serial.println(F("*****************"));
}

// ----------------------------------------------------------------------------------------------
COMMAND_TYPE Comms::getCommandType() {
    return packetBuffer[1];
}

// ----------------------------------------------------------------------------------------------
// Return true if the button is pressed on the app.
//
bool Comms::buttonIsPressed() {
    return packetBuffer[3] == BUTTON_PRESSED;
}

// ----------------------------------------------------------------------------------------------
// Return the value of the button that was pressed on the app.
//
char Comms::getButtonValue() {
    return packetBuffer[2];
}

// ----------------------------------------------------------------------------------------------
// Return the float values for those commands that send that data. Some commands send three while
// just one sends four. Call with getFourthFloat set to true to read four floats, or false to
// just read three.
//
DataFourFloats& Comms::getFloats(bool getFourthFloat) {
    memcpy(&dff.x, &packetBuffer[2],  sizeof(dff.x));
    memcpy(&dff.y, &packetBuffer[6],  sizeof(dff.y));
    memcpy(&dff.z, &packetBuffer[10], sizeof(dff.z));

    if (getFourthFloat) {
        memcpy(&dff.w, &packetBuffer[14], sizeof(dff.w));
    }
    else {
        dff.w = 0.0;
    }
 
    return dff;
}

// ----------------------------------------------------------------------------------------------

void Comms::error(const __FlashStringHelper *err) {
    Serial.println(err);
    while (true);
}

// ----------------------------------------------------------------------------------------------
// Prints a hexadecimal value in plain characters
// data      Pointer to the byte data
// numBytes  Data length in bytes
// ----------------------------------------------------------------------------------------------

void Comms::printHex(const uint8_t * data, const uint32_t numBytes) {
    uint32_t szPos;
 
    for (szPos=0; szPos < numBytes; szPos++) {
        Serial.print(F("0x"));

        // Append leading 0 for small values
        //
        if (data[szPos] <= 0xF) {
            Serial.print(F("0"));
            Serial.print(data[szPos] & 0xf, HEX);
        }
        else {
            Serial.print(data[szPos] & 0xff, HEX);
        }

        // Add a trailing space if appropriate
        //
        if ((numBytes > 1) and (szPos != numBytes - 1)) {
            Serial.print(F(" "));
        }
    }

    Serial.println();
}

// ----------------------------------------------------------------------------------------------
// Waits for incoming data and loads it into packetBuffer.
// Returns 0 if nothing recieved to process, or greater than zero if a command (package) is
// recieved.
// ----------------------------------------------------------------------------------------------

uint8_t Comms::readData() {
    uint16_t initialTimeout = BLE_READPACKET_TIMEOUT;
    uint16_t timeout = initialTimeout;
    uint16_t bufferIndex = 0;

    memset(packetBuffer, 0, MAX_PACKET_BUFSIZE);

    // We wait until timeout reaches zero, the bufferIndex is maxed out, or we recieved a
    // command packet. The logic of the while loop makes sure we stay in the while loop as
    // long as none of the exit criteria have been reached.
    //
    while (timeout-- and (bufferIndex < MAX_PACKET_BUFSIZE) and (not packetBuffer[1])) {

        // We will wait in this loop until an entire packet is recieved and built. Because
        // a packet from the Adafruit Bluefruit LE Connect app sends all its commands
        // prefixed with a '!' character, that is what we'll wait for and begin to construct
        // the packet behind that first character.
        //
        while (ble->available()) {
            char c =  ble->read();
            if (c == START_CMD) {
                bufferIndex = 0;
            }

            packetBuffer[bufferIndex++] = c;
            timeout = initialTimeout;
        }
    }

    // We may have timed out waiting for something, so make sure we return nothing.
    //
    if (timeout == 0) {
        bufferIndex = 0;
    }

    return bufferIndex;
}
