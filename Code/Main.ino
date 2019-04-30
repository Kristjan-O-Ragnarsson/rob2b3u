// Import the defines and classes
#include "inc/Defines.h"
#include "inc/Button.h"
#include "inc/MotorController.h"

// Create instances of the classes
Button btn = Button();
MotorController mc = MotorController();

void setup() {
	btn.ButtonSetup(); // Set up the button
	mc.MotorControllerSetup(); // Set up the motor controller and camera
}

void loop() {
	btn.ButtonLoop(); // Check if the button was pressed
	mc.MotorChangeSpeed(150);

	if(running) // Drive
		mc.MotorControllerLoop();
	else // Stop
		mc.MotorStop();
}