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

#include <Arduino.h>

#include "Motor.h"
#include "Utilities.h"

// -----------------------------------------------------------------------------
//
Motor::Motor() {
}

// -----------------------------------------------------------------------------
//
void Motor::setup() {
  // Create the motor shield object with the default I2C address
  //
  AFMS = Adafruit_MotorShield();

  // And connect 2 DC motors to ports M3 & M4 !
  //
  LEFT_MOTOR = AFMS.getMotor(4);
  RIGHT_MOTOR = AFMS.getMotor(3);

  // create with the default frequency 1.6KHz
  //
  AFMS.begin();

  // Enable motors, make sure they are not turning.
  //
  fullStop();
}

// -----------------------------------------------------------------------------
//
void Motor::forward() {
  checkSetup();
  LEFT_MOTOR->run(FORWARD);
  RIGHT_MOTOR->run(FORWARD);
  maxSpeed = ForwardSpeed;
}

// -----------------------------------------------------------------------------
//
void Motor::backward() {
  checkSetup();
  LEFT_MOTOR->run(BACKWARD);
  RIGHT_MOTOR->run(BACKWARD);
  maxSpeed = ReverseSpeed;
}

// -----------------------------------------------------------------------------
//
void Motor::turnLeft() {
  checkSetup();
  LEFT_MOTOR->run(RELEASE);
  RIGHT_MOTOR->run(FORWARD);
  maxSpeed = TurningSpeed;
}

// -----------------------------------------------------------------------------
//
void Motor::turnRight() {
  checkSetup();
  LEFT_MOTOR->run(FORWARD);
  RIGHT_MOTOR->run(RELEASE);
  maxSpeed = TurningSpeed;
}

// -----------------------------------------------------------------------------
//
void Motor::accelerate() {
  checkSetup();

  while (currentSpeed < maxSpeed) {
    currentSpeed += 3;
    LEFT_MOTOR->setSpeed(currentSpeed);
    RIGHT_MOTOR->setSpeed(currentSpeed);
    delay(5);
  }
}

// -----------------------------------------------------------------------------
//
void Motor::fullStop() {
  checkSetup();
  LEFT_MOTOR->setSpeed(0);
  LEFT_MOTOR->run(RELEASE);
  RIGHT_MOTOR->setSpeed(0);
  RIGHT_MOTOR->run(RELEASE);
  currentSpeed = maxSpeed = 0;
}

// -----------------------------------------------------------------------------
//
void Motor::checkSetup() {
  if (!LEFT_MOTOR) errorHalt(F("LEFT_MOTOR is NULL! Did you call setup?"));
  if (!RIGHT_MOTOR) errorHalt(F("RIGHT_MOTOR is NULL! Did you call setup?"));
}
