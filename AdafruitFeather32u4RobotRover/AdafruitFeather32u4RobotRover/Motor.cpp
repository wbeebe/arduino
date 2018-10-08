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

#include "Motor.h"

// ----------------------------------------------------------------------------------------------

Motor::Motor() {
    // Create the motor shield object with the default I2C address
    //
    AFMS = Adafruit_MotorShield();

    // And connect 2 DC motors to ports M3 & M4 !
    //
    LEFT_MOTOR = AFMS.getMotor(4);
    RIGHT_MOTOR = AFMS.getMotor(3);
}

// ----------------------------------------------------------------------------------------------

void Motor::setup() {
    // create with the default frequency 1.6KHz
    //
    AFMS.begin();

    // Enable motors, make sure they are not turning.
    //
    fullStop();
}

// ----------------------------------------------------------------------------------------------

void Motor::forward() {
    LEFT_MOTOR->run(FORWARD);
    RIGHT_MOTOR->run(FORWARD);
    maxspeed = ForwardSpeed;
}

// ----------------------------------------------------------------------------------------------

void Motor::backward() {
    LEFT_MOTOR->run(BACKWARD);
    RIGHT_MOTOR->run(BACKWARD);
    maxspeed = ReverseSpeed;
}

// ----------------------------------------------------------------------------------------------

void Motor::turnLeft() {
    LEFT_MOTOR->run(RELEASE);
    RIGHT_MOTOR->run(FORWARD);
    maxspeed = TurningSpeed;
}

// ----------------------------------------------------------------------------------------------

void Motor::turnRight() {
    LEFT_MOTOR->run(FORWARD);
    RIGHT_MOTOR->run(RELEASE);
    maxspeed = TurningSpeed;        
}

// ----------------------------------------------------------------------------------------------

void Motor::accelerate() {
    for (int speed=0; speed < maxspeed; speed+=5) {
        LEFT_MOTOR->setSpeed(speed);
        RIGHT_MOTOR->setSpeed(speed);
        delay(5);
    }
}

// ----------------------------------------------------------------------------------------------

void Motor::decelerate() {
    for (int speed = maxspeed; speed >= 0; speed-=5) {
        LEFT_MOTOR->setSpeed(speed);
        RIGHT_MOTOR->setSpeed(speed);
        delay(5);
    }
}

// ----------------------------------------------------------------------------------------------

void Motor::fullStop() {
    LEFT_MOTOR->setSpeed(0);
    LEFT_MOTOR->run(RELEASE);
    RIGHT_MOTOR->setSpeed(0);
    RIGHT_MOTOR->run(RELEASE);
}
