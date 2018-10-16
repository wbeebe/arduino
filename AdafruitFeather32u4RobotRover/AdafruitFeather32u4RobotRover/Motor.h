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

#ifndef MOTOR_H
#define MOTOR_H

#include <Adafruit_MotorShield.h>

// ----------------------------------------------------------------------------------------------
// Set your forward, reverse, and turning speeds
// ----------------------------------------------------------------------------------------------

#define ForwardSpeed    100
#define ReverseSpeed    100
#define TurningSpeed    100

// ----------------------------------------------------------------------------------------------

class Motor {
    private:
    uint8_t maxspeed;
    Adafruit_MotorShield AFMS;
    Adafruit_DCMotor *LEFT_MOTOR;
    Adafruit_DCMotor *RIGHT_MOTOR;

    void error(const __FlashStringHelper *);
    void checkSetup();

    public:
    Motor();

    void setup();

    void forward();

    void backward();

    void turnLeft();

    void turnRight();

    void accelerate();

    void decelerate();

    void fullStop();
};

#endif
