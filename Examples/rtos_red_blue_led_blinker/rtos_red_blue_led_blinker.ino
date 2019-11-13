/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include <Arduino.h>

/**
 * Sketch demonstate mutli-task using Scheduler.
 * Demo creates a loop2() that runs in 'parallel' with loop().
 * - loop() toggles LED_RED every 1 second
 * - loop2() toggles LED_BLUE every 300 milliseconds
 */

void setup() {
    // whb Nov 2019
    // This must be performed first or else nothing else will work.
    // No, I don't know exactly why.
    //
    Serial.begin(115200);

    // LED_RED & LED_BLUE pins are already initialized outputs.
    // Create loop2() using Scheduler to run in 'parallel' with loop()
    //
    Scheduler.startLoop(loop2);
}

/**
 * Toggle the Red LED every second
 */
void loop() {
    digitalToggle(LED_RED); // Toggle LED 
    delay(1000);            // wait for a second
}

/**
 * Toggle the Blue LED every 300 milliseconds
 */
void loop2() {
    digitalToggle(LED_BLUE); // Toggle LED 
    delay(300);              // wait for a half second  
}
