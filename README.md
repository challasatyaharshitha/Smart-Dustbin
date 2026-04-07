#Smart Automated Trash Bin
#Overview

This project implements an automated trash bin that opens its lid when a user approaches, using an ultrasonic sensor for proximity detection and a servo motor for lid movement. A manual override button is included to allow direct user control, improving usability and flexibility.

#Technologies / Tools
Arduino (C++)
Ultrasonic Sensor (HC-SR04)
Servo Motor (SG90)
Push Button
#Key Features
*Proximity-based automatic lid opening
*Manual override control using push button (toggle open/close)
*Real-time distance sensing
*Reduced false triggering using:
Averaging of multiple sensor readings
Distance thresholding
Value constraining
*Reliable sensor-to-actuator integration
