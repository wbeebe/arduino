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
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

void writeAllDigitAscii(uint8_t character) {
    alpha4.writeDigitAscii(0, character, true);
    alpha4.writeDigitAscii(1, character, true);
    alpha4.writeDigitAscii(2, character, true);
    alpha4.writeDigitAscii(3, character, true);
    alpha4.writeDisplay();    
}

/**
 * Simple digital down counter with .1 second resolution,
 * more or less.
 * Call with whole seconds to count down.
 * Function multiplies by ten to increase value for .1 second
 * countdown on display.
 */
void secondsDownCounter(int downcount) {
    for (int i = downcount * 10; i >= 0; i--) {
        alpha4.writeDigitAscii(0, ((i / 1000) % 10 + '0'));
        alpha4.writeDigitAscii(1, ((i / 100) % 10 + '0'));
        //
        // Put a decimal on this digit to indicate tenth of a second.
        //
        alpha4.writeDigitAscii(2, ((i / 10) % 10 + '0'), true);
        alpha4.writeDigitAscii(3, (i % 10 + '0'));
        alpha4.writeDisplay();
        delay(100);
    }
}

void setup() {
    Serial.begin(115200);
    alpha4.begin(0x70);
    Scheduler.startLoop(loopBlinkBlue);
    Scheduler.startLoop(loopEcho);
    //
    // Disable loopBlinkRed, as its control line
    // is used for the I2C pins communicating with the
    // alpha display plugged into the nRF52 feather.
    //
    // Scheduler.startLoop(loopBlinkRed);
}

void loop() {
    while(true) {
        secondsDownCounter(30);
        //
        // Get all fancy and flash the displays alternately with
        // all zeros then blanks ten times.
        //
        for (int j = 10; j > 0; j--) {
            writeAllDigitAscii('0');
            delay(100);
            writeAllDigitAscii(' ');
            delay(100);
        }
    }
}

void loopBlinkBlue() {
    while(true) {
        digitalWrite(LED_BLUE, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(500);                     // wait for 500 ms
        digitalWrite(LED_BLUE, LOW);    // turn the LED off by making the voltage LOW
        delay(250);                     // wait for 250 ms
    }
}

void loopEcho() {
    while(true) {
        if (Serial.available()) {
            Serial.write(Serial.read());
        }
    }
}

void loopBlinkRed() {
    while(true) {
        digitalWrite(LED_RED, HIGH);    // turn the LED on (HIGH is the voltage level)
        delay(250);                     // wait for 250 ms
        digitalWrite(LED_RED, LOW);     // turn the LED off by making the voltage LOW
        delay(1750);                    // wait for 1.75 seconds
    }
}
