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

#ifndef UTILITIES_H_
#define UTILITIES_H_

// -----------------------------------------------------------------------------
// Templated printHex. Instantiate with the variable you want to print out in
// hexadecimal as the argument call.
//
extern char hexDigits[];

template<typename T> void printHex(T value) {
    uint8_t *vptr = reinterpret_cast<uint8_t *>(&value);
    for (int i = 0; i < sizeof(value); i++) {
        Serial.print(hexDigits[static_cast<int>((vptr[i] >> 4) & 0x0f)]);
        Serial.print(hexDigits[static_cast<int>(vptr[i] & 0x0f)]);
    }
    Serial.print(' ');
}

// -----------------------------------------------------------------------------
// Send an error string out to the Serial Monitor console and then halt.
// Function does not return and the application is locked at this point
// until it's reset.
//
void errorHalt(const __FlashStringHelper *);

#endif  // UTILITIES_H_
