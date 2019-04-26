#include "inc/Defines.h"
#include "inc/Button.h"

bool startOnPush = true, released = true, running = false;

void buttonLoop() {
	digitalWrite(13, running);

	if (released && digitalRead(BUTTON_SIGNAL_PIN)) {
		released = false;
		running = !running;
		startOnPush = !startOnPush;
	} else if(!released && !digitalRead(BUTTON_SIGNAL_PIN)) {
		released = true;
	}

	if (DEBUG)
		buttonDebugInfo(false, false);
}

void buttonSetup() {
	pinMode(BUTTON_SIGNAL_PIN, INPUT);
	pinMode(LED_BUILTIN, OUTPUT);
}

void setRunning(bool newVal) {
	running = newVal;
}

bool getRunning() {
	return running;
}

void buttonDebugInfo(bool showBools, bool showDefines, bool showValue = true) {
	if (showValue) {
		Serial.print("Button value: ");
		Serial.println(digitalRead(BUTTON_SIGNAL_PIN));
	}

	if (showBools) {
		Serial.print("Released: ");
		Serial.println(released);
		Serial.print("Start on push: ");
		Serial.println(startOnPush);
		Serial.print("Running: ");
		Serial.println(running);
	}
	
	if (showDefines) {
		Serial.print("Button signal pin: ");
		Serial.println(BUTTON_SIGNAL_PIN);
	}
}