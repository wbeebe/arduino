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

#ifndef MELODY_H
#define MELODY_H

/*********************************************************************
   Software derived Pulse-Width Modulatoin (PWM) tone and melody
   playback software.

   Derived from original work by Tiaga Galo:
   https://therandombit.wordpress.com/2011/11/21/arduino-piezo-speaker-super-mario/

   Modified to run on Adafruit Feather 32u4 Bluefruit LE:
   https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/overview
 *********************************************************************/

// ----------------------------------------------------------------------------------------------
// Definition of certain musical notes.
// ----------------------------------------------------------------------------------------------

enum NOTES {
  _C   = 1911,
  _C1  = 1804,
  _D   = 1703,
  _Eb  = 1607,
  _E   = 1517,
  _F   = 1432,
  _F1  = 1352,
  _G   = 1276,
  _Ab  = 1204,
  _A   = 1136,
  _Bb  = 1073,
  _B   = 1012,
  _c   = 955,
  _c1  = 902,
  _d   = 851,
  _eb  = 803,
  _e   = 758,
  _f   = 716,
  _f1  = 676,
  _g   = 638,
  _ab  = 602,
  _a   = 568,
  _bb  = 536,
  _b   = 506,
};

// ----------------------------------------------------------------------------------------------
// Pin used to drive the speaker on the Adafruit Feather 32u4
// Bluefruit LE board
// ----------------------------------------------------------------------------------------------

#define speakerPin A1

// ----------------------------------------------------------------------------------------------
// A value, which multiplied with the note's duration in microseconds,
// provides the amount of total time to play the note.
// ----------------------------------------------------------------------------------------------

#define rate  20000L

// ----------------------------------------------------------------------------------------------
// A melody is defined as an array of arrays:
//
// melody[][2]
//
// where the first value in the second array is the note,
// and the second value in the second array is the note's duration
// in microseconds. A special value, known as the rate (see above)
// is multiplied by the note's duration to determine how long to truly
// allow the note to play.
//
// The train of notes is termintes with a {0,0} so that the melody playback
// function will know where the array stops, and thus the music.
// Notice that the array can be of any size, as long as it's terminated with {0,0}
// ----------------------------------------------------------------------------------------------

using sequence_t = int[][2];

extern sequence_t SuperMarioBrosMelody;
extern sequence_t PeerGyntMelody;
extern sequence_t SmokeMelody;
extern sequence_t NatalMelody;

// ----------------------------------------------------------------------------------------------

class Melody {
  public:
    Melody();

    // This class function plays a melody as defined above.
    // It iterates down the array of notes, until it reaches
    // an entry with a zero value in the note location, at which point it stops.
    // This is behavior similar to iterating a C string to the end.
    //
    void play(sequence_t);

  private:
    void playNote(int note[2]);
};

#endif
