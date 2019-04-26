#include "inc/Defines.h"

#include "inc/Button.h"
#include "inc/MotorController.h"

void setup() {
	buttonSetup();
	motorControllerSetup();
}

void loop() {
	buttonLoop();
	motorControllerLoop();
}