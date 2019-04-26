#include "inc/Defines.h"
#include <Pixy2.h>

Pixy2 camera; // Camera object

bool lReverse = true; // Left motor reverse
bool rReverse = true; // Right motor reverse

int speed = 100; // The motor speed (0 - 255)

int enablePins[] = {FR_ENABLE, BR_ENABLE, FL_ENABLE, BL_ENABLE}; // Motor enable pins
int inPins[] = {IN1_R, IN2_R, IN3_R, IN4_R, IN1_L, IN2_L, IN3_L, IN4_L}; // Motor in pins

void motorControllerSetup() {
	// Camera
	Serial.begin(BAUD); // Open the Camera serial connection

	camera.init(); // Initialize the camera connection
	camera.changeProg("line"); // Set the camera program to line follower
	camera.setLamp(0, 0); // Set the lamps (lights) on the camera (0 = off, 1 = on)

	// Set the motor pins to output mode
	for(int i = 0; i < 12; i++) {
		if(i < 4) // The first 4 are the enable pins
			pinMode(enablePins[i], OUTPUT);
	  	else // The other pins
			pinMode(inPins[i - 4], OUTPUT);
	}

	setMotorSpeed(); // Set the motor speed to the default (defined above)
}

void motorControllerLoop() {
	camera.line.getAllFeatures(1 | 2, false);

	if(camera.line.numIntersections == 0) {
		int startX = camera.line.vectors[0].m_x0;

		if(startX < CAMERA_MIDDLE_X - CAMERA_DEADZONE) {
			turnLeft();
			//Serial.println("Turn left");
		}
		else if(startX > CAMERA_MIDDLE_X + CAMERA_DEADZONE) {
			turnRight();
			//Serial.println("Turn right");
		}
		else {
			driveForward();
			//Serial.println("Drive forward");
		}
	} else {
		// TODO: Intersection code
	}

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

	delay(100);
}

void motorChangeSpeed(int sp) {
	if(sp < MIN_MOTOR_SPEED)
		sp = MIN_MOTOR_SPEED;
	else if(sp > MAX_MOTOR_SPEED)
		sp = MAX_MOTOR_SPEED;

	speed = sp;

	setMotorSpeed();
}

void setMotorSpeed() {
	for(int i = 0; i < 4; i++)
		analogWrite(enablePins[i], speed);
}

void motorStop() {
	for(int i = 0; i < 8; i++)
		digitalWrite(inPins[i], LOW);
}

void driveForward() {
	lReverse = false;
	rReverse = false;

	setMotorSpeed();

	motorWrite();
}

void driveBackwards() {
	lReverse = true;
	rReverse = true;

	setMotorSpeed();

	motorWrite();
}

void turnRight() {
	lReverse = false;
	rReverse = true;

	//lReverse = false;
	//rReverse = false;

	analogWrite(FR_ENABLE, MIN_MOTOR_SPEED);
	analogWrite(BR_ENABLE, MIN_MOTOR_SPEED);
	analogWrite(FL_ENABLE, MIN_MOTOR_SPEED);
	analogWrite(BL_ENABLE, MIN_MOTOR_SPEED);

	motorWrite();
}

void turnLeft() {
	lReverse = true;
	rReverse = false;

	//lReverse = false;
	//rReverse = false;

	analogWrite(FR_ENABLE, MIN_MOTOR_SPEED);
	analogWrite(BR_ENABLE, MIN_MOTOR_SPEED);
	analogWrite(FL_ENABLE, MIN_MOTOR_SPEED);
	analogWrite(BL_ENABLE, MIN_MOTOR_SPEED);

	motorWrite();
}

void motorWrite() {
	for(int i = 0; i < 4; i++)
		digitalWrite(inPins[i], (i % 2 == 0) ? !rReverse : rReverse);

	for(int i = 4; i < 8; i++)
		digitalWrite(inPins[i], (i % 2 == 0) ? !lReverse : lReverse);
}