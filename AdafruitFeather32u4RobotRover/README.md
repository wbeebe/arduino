# AdafruitFeather32u4RobotRover

This is an application designed to operate the Adafruit AdaBox002 Feather Bluetooth LE Mini Robot (https://www.adafruit.com/product/3235). The kit from Adafruit is powered by the Adafruit Feather 32u4 Bluefruit LE (https://www.adafruit.com/product/2829) for which this software is written.

The software was developed using the Arduino IDE Version 1.8.7 (https://www.arduino.cc/en/Main/Software).

It was tested using the Adafruit Bluefruit LE Connect app, Version 3.3.2, on both iOS (12.1) and Android (7.1).

It is written to move the Mini Robot and to play back four melodies via the bottons provided by the Adafruit app. It is written in C++.

## Avialable Files

+ AdafruitFeather32u4RobotRover.ino - The core of the application. The functions setup() and loop() are specific to this file. Setup is called when the embedded application is first started, and is only called once. The loop function is then called next. This is where all the work is done. Loop does exactly what it says, it loops and does not return.

+ BluefruitConfig.h - Several basic configuration settings specific to the Feather's Bluetooth hardware.

+ Comms (.h and .cpp) - A class that wraps the basic initialization and operational functionality for the Bluetooth LE (BLE) wireless communications. In addition to setting up the BLE subystems, it also provides helper functions to read and send data across the BLE wireless link. Helper functions include determining which button was pushed as well as reading single precision floating point numbers from the BLE raw byte stream.

+ Melody (.h and .cpp) - A class that wraps the ability to play back simple melodies via software Pulse Width Modulation (PWM) using one of the Feature's pins to drive a simple audio emitter.

+ Motor (.h and .cpp)

+ Utilities (.h and .cpp)

## License

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
