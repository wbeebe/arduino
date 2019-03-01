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

/*
   This uses some example code for the nRF51822 based Adafuit Bluefruit LE modules
   provided by Adafruit.

   Adafruit invests time and resources providing this open source code,
   please support Adafruit and open-source hardware by purchasing
   products from Adafruit!

   Some portions use MIT license, check LICENSE for more information
   All text above, and the splash screen below must be included in
   any redistribution
*/

#pragma once

// -----------------------------------------------------------------------------
// COMMON SETTINGS
//
// These constants are used in both SW UART, HW UART and SPI mode
//
const boolean VERBOSE_MODE = true;      // If set to 'true' enables debug output
const int BLE_READPACKET_TIMEOUT = 500; // Timeout in ms waiting to read a response

// -----------------------------------------------------------------------------
// SHARED SPI SETTINGS
//
// Define the pins to use for HW and SW SPI communication.
// SCK, MISO and MOSI should be connected to the HW SPI pins on the Uno when
// using HW SPI.  This should be used with nRF51822 based Bluefruit LE modules
// that use SPI (Bluefruit LE SPI Friend).
//
const int BLUEFRUIT_SPI_CS = 8;
const int BLUEFRUIT_SPI_IRQ = 7;
const int BLUEFRUIT_SPI_RST = 4;    // Optional but recommended, set to -1 if unused
