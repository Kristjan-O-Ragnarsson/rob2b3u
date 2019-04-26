// Import the defines and motor controller class
#include "inc/Defines.h"
#include "inc/MotorController.h"

// Set up the motor controller and camera
void MotorController::MotorControllerSetup() {
	// Camera
	Serial.begin(BAUD); // Open the Camera serial connection

	camera.init(); // Initialize the camera connection
	camera.changeProg("line"); // Set the camera program to line follower
	camera.setLamp(1, 0); // Set the lamps (lights) on the camera (0 = off, 1 = on)
	camera.line.setMode(LINE_MODE_WHITE_LINE); // Follow a white line

	// Set the motor pins to output mode
	for(int i = 0; i < 12; i++) {
		if(i < 4) // The first 4 are the enable pins
			pinMode(enablePins[i], OUTPUT);
	  	else // The other pins
			pinMode(inPins[i - 4], OUTPUT);
	}

	SetMotorSpeed(); // Set the motor speed to the default (defined above)
}

// The main motor controller loop
void MotorController::MotorControllerLoop() {
	camera.line.getMainFeatures(1 | 2, false); // 1 = LINE_VECTOR, 2 = LINE_INTERSECTION, 4 = LINE_BARCODE; Wait: false = return immediatley if no line is found.

	// No intersections
	if(camera.line.numIntersections == 0) {
		int startX = camera.line.vectors->m_x0; // Get the start x of the first line

		// If the start x is left of the center
		if(startX < CAMERA_MIDDLE_X - CAMERA_DEADZONE) {
			TurnLeft();
			//Serial.println("Turn left");
		}
		else if(startX > CAMERA_MIDDLE_X + CAMERA_DEADZONE) { // If the start x is right of the center
			TurnRight();
			//Serial.println("Turn right");
		}
		else { // If the start x is in the center
			DriveForward();
			//Serial.println("Drive forward");
		}
	} else { // If tere is an intersection
		// TODO: Intersection code
	}

	// If the DEBUG flag is set to true
	if(DEBUG) {
		int8_t i;
		char buf[128];

		// Print all vectors
		for(i = 0; i < camera.line.numVectors; i++) {
			sprintf(buf, "line %d: ", i);
			Serial.print(buf);
			camera.line.vectors[i].print();
		}

		// Print all intersections
		for(i = 0; i < camera.line.numIntersections; i++) {
			sprintf(buf, "intersection %d: ", i);
			Serial.print(buf);
			camera.line.intersections[i].print();
		}
	}

	Serial.flush();
	delay(50); // Let the camera process and return the lines
}

// Change the motor speed
void MotorController::MotorChangeSpeed(int sp) {
	if(sp < MIN_MOTOR_SPEED) // If the speed is set lower than the min value
		sp = MIN_MOTOR_SPEED; // Set the speed to the min value
	else if(sp > MAX_MOTOR_SPEED) // If the speed is set higher than the max value
		sp = MAX_MOTOR_SPEED; // Set the speed to the max value

	speed = sp; // Set the speed

	SetMotorSpeed(); // Apply the speed to the motors
}

// Apply the speed to the motors
void MotorController::SetMotorSpeed() {
	for(int i = 0; i < 4; i++) // For each enable pin
		analogWrite(enablePins[i], speed); // Set the speed
}

// Stop all motors
void MotorController::MotorStop() {
	for(int i = 0; i < 8; i++) // For each in pin
		digitalWrite(inPins[i], LOW); // Turn the pin off
}

// Drive forward in a straight line
void MotorController::DriveForward() {
	lReverse = false; // Don't reverse the left motors
	rReverse = false; // Don't reverse the right motors

	SetMotorSpeed(); // Apply the motor speed
	MotorWrite(); // Write the direction of the motors
}

// Drive backwards in a straight line
void MotorController::DriveBackwards() {
	lReverse = true; // Reverse the left motors
	rReverse = true; // Reverse the right motors

	SetMotorSpeed(); // Apply the motor speed
	MotorWrite(); // Write the direction of the motors
}

// Turn right
void MotorController::TurnRight() {
	lReverse = false; // Don't reverse the left motors
	rReverse = true; // Reverse the right motors

	// Set the speed of the motors to the min speed
	analogWrite(FR_ENABLE, TURN_SPEED);
	analogWrite(BR_ENABLE, TURN_SPEED);
	analogWrite(FL_ENABLE, TURN_SPEED);
	analogWrite(BL_ENABLE, TURN_SPEED);

	MotorWrite(); // Write the direction of the motors
}

// Turn left
void MotorController::TurnLeft() {
	lReverse = true; // Reverse the left motors
	rReverse = false; // Don't reverse the right motors

	// Set the speed of the motors to the min speed
	analogWrite(FR_ENABLE, TURN_SPEED);
	analogWrite(BR_ENABLE, TURN_SPEED);
	analogWrite(FL_ENABLE, TURN_SPEED);
	analogWrite(BL_ENABLE, TURN_SPEED);

	MotorWrite(); // Write the direction of the motors
}

// Write the motor direction to the motor controller
void MotorController::MotorWrite() {
	for(int i = 0; i < 4; i++) // For each right in pin
		digitalWrite(inPins[i], (i % 2 == 0) ? !rReverse : rReverse); // Alternate the right reverse bool

	for(int i = 4; i < 8; i++) // For each left in pin
		digitalWrite(inPins[i], (i % 2 == 0) ? !lReverse : lReverse); // Alternate the left reverse bool
}