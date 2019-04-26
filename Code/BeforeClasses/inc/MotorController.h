#ifndef _MOTOR_CONTROLLER_H_
#define _MOTOR_CONTROLLER_H_

void motorControllerSetup();
void motorControllerLoop();
void motorChangeSpeed(int);
void setMotorSpeed();
void motorStop();
void driveForward();
void driveBackwards();
void turnRight();
void turnLeft();
void motorWrite();

#endif // _MOTOR_CONTROLLER_H_