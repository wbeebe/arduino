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

#include <Arduino.h>
#include "Melody.h"

sequence_t SuperMarioBrosMelody = {
    {_e, 6},    // The original first seven notes from Tiaga Galo's
    {_e, 12},   // post, added back in again.
    {_e, 12},
    {_c, 6},
    {_e, 12},
    {_g, 24},
    {_G, 24},
    
    {_c, 18},
    {_G, 18},
    {_E, 18},
    {_A, 12},
    {_B, 12},
    {_Bb, 6},

    {_A, 12},
    {_G, 8},
    {_e, 8},
    {_c, 8},
    {_a, 12},
    {_f, 6},

    {_g, 12},
    {_e, 12},
    {_c, 6},
    {_d, 6},
    {_B, 6},
    {0,0},
};

// From Tiaga Galo's post
//
sequence_t PeerGyntMelody = {
    {_G, 8},
    {_E, 8},
    {_D, 8},
    {_C, 8},
    {_D, 8},
    {_E, 8},
    {_G, 8},
    {_E, 8},
    {_D, 8},
    {_C, 8},
    {_D, 4},
    {_E, 4},
    {_D, 4},
    {_E, 4},
    {_G, 8},
    {_E, 8},
    {_G, 8},
    {_A, 8},
    {_E, 8},
    {_A, 8},
    {_G, 8},
    {_E, 8},
    {_D, 8},
    {_C, 16},
    {0,0},
};

sequence_t SmokeMelody = {
    {_E, 12},
    {_G, 12},
    {_A, 18},
    {_E, 12},
    {_G, 12},
    {_Bb, 6},
    {_A, 18},
    {_E, 12},
    {_G, 12},
    {_A, 18},
    {_G, 12},
    {_E, 24},
    {0,0},
};

sequence_t NatalMelody = {
    {_G, 12},
    {_A, 4},
    {_G, 8},
    {_E, 16},
    {_G, 12},
    {_A, 4},
    {_G, 8},
    {_E, 16},
    {_c, 12},
    {_c, 4},
    {_A, 16},
    {_B, 12},
    
    {_B, 4},
    {_G, 16},
    {_A, 12},
    {_G, 4},
    {_A, 8},
    {_c, 8},
    {_B, 8},
    {_A, 8},
    {_G, 12},
    {_A, 4},
    {_G, 8},
    {_E, 16},
    {0,0},
};

// ----------------------------------------------------------------------------------------------
// Called during instantiation, sets up hardware output pin.
// ----------------------------------------------------------------------------------------------

Melody::Melody() {
    // Set the melody software PWM speaker pin to output
    //
    pinMode(speaker, OUTPUT);
}

// ----------------------------------------------------------------------------------------------
// Called with an array of two-element arrays, will play the entire array until it reaches the
// end.
// ----------------------------------------------------------------------------------------------

void Melody::play(sequence_t melody) {
    for (int i = 0; melody[i][0]; i++) {
        playNote(melody[i]);
        delayMicroseconds(10000);
    }
}

// ----------------------------------------------------------------------------------------------
// This function plays a single note via software pulse-width modulation, or PWM.
// Because this particular board supports hardware PWM, this function will be replaced
// in the near future with code that uses one of the pins in PWM mode.
// ----------------------------------------------------------------------------------------------

void Melody::playNote(int note[2]) {
    long timeSpent = 0;
    long duration = note[1] * rate;

    while (timeSpent < duration) {
        digitalWrite(speaker, HIGH);
        delayMicroseconds(note[0]/2);
        digitalWrite(speaker, LOW);
        delayMicroseconds(note[0]/2);
        timeSpent += note[0];
    }
}
