#ifndef _MOTOR_CONTROLLER_H_
#define _MOTOR_CONTROLLER_H_

#include <Pixy2.h> // Import the camera library

class MotorController {
public:
	void MotorControllerSetup(); // Sets up the motors and camera
	void MotorControllerLoop(); // The drive loop
	void MotorChangeSpeed(int); // Change the motor speed
	void SetMotorSpeed(); // Write the motor speed to the controller
	void MotorStop(); // Stop the motors
	void DriveForward(); // Drives forward in a straight line
	void DriveBackwards(); // Drives backwards in a straight line
	void TurnRight(); // Turn to the right
	void TurnLeft(); // Turn to the left
	void MotorWrite(); // Write info to the motor controller

private:
	Pixy2 camera; // Camera object

	bool lReverse = true; // Left motor reverse
	bool rReverse = true; // Right motor reverse

	int speed = 100; // The motor speed (0 - 255)

	int enablePins[4] = {FR_ENABLE, BR_ENABLE, FL_ENABLE, BL_ENABLE}; // Motor enable pins
	int inPins[8] = {IN1_R, IN2_R, IN3_R, IN4_R, IN1_L, IN2_L, IN3_L, IN4_L}; // Motor in pins
};

#endif // _MOTOR_CONTROLLER_H_