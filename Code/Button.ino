// Import the defines and button class
#include "inc/Defines.h"
#include "inc/Button.h"

// Set up the button
void Button::ButtonSetup() {
	pinMode(BUTTON_SIGNAL_PIN, INPUT);
	//pinMode(LED_BUILTIN, OUTPUT); // To turn the onboard LED on or off
}

// The main button loop
void Button::ButtonLoop() {
	//digitalWrite(13, running); // Turn the onboard LED on and off depending if the program is running

	// If the button has been released and is being pressed
	if (released && digitalRead(BUTTON_SIGNAL_PIN)) {
		released = false; // Don't enter this if statement again if the button has not been released
		running = !running; // Flip the running flag
		startOnPush = !startOnPush; // Flip the start on push flag
	} else if(!released && !digitalRead(BUTTON_SIGNAL_PIN)) { // If the button is released
		released = true; // The button can now be pressed again
	}

	// If the DEBUG flag is set to true
	if (DEBUG)
		ButtonDebugInfo(false, false, false); // Write out debug info
}

// Prints button debug info to the serial monitor
void Button::ButtonDebugInfo(bool showBools, bool showDefines, bool showValue = true) {
	// Show the button value?
	if (showValue) {
		Serial.print("Button value: ");
		Serial.println(digitalRead(BUTTON_SIGNAL_PIN));
	}

	// Show the booleans the button controls?
	if (showBools) {
		Serial.print("Released: ");
		Serial.println(released);
		Serial.print("Start on push: ");
		Serial.println(startOnPush);
		Serial.print("Running: ");
		Serial.println(running);
	}
	
	// Show defines related to the button?
	if (showDefines) {
		Serial.print("Button signal pin: ");
		Serial.println(BUTTON_SIGNAL_PIN);
	}
}