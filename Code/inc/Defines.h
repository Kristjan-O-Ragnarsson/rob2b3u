#ifndef _DEFINES_H_
#define _DEFINES_H_

// Common
#define DEBUG false
bool running = false; // Is the robot driving?

// Button
#define BUTTON_SIGNAL_PIN 22

// Camera
#define BAUD 115200

#define CAMERA_MIDDLE_X 39
#define CAMERA_DEADZONE 5

// Motors
#define MIN_MOTOR_SPEED 60
#define MAX_MOTOR_SPEED 255
#define TURN_SPEED 80

// Front right motor
#define FR_ENABLE 2
#define IN1_R 3
#define IN2_R 4

// Back right motor
#define BR_ENABLE 5
#define IN3_R 6
#define IN4_R 7

// Front left motor
#define FL_ENABLE 8
#define IN1_L 9
#define IN2_L 10

// Back left motor
#define BL_ENABLE 11
#define IN3_L 12
#define IN4_L 13

// Sonar
#define TRIGGER_PIN A3
#define ECHO_PIN A2

#endif // _DEFINES_H_