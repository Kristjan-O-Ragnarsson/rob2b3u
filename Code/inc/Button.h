#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button {
public:
	void ButtonSetup(); // The button setup
	void ButtonLoop(); // The main button loop
	void ButtonDebugInfo(bool, bool, bool = true); // Writes button debug info

private:
	bool startOnPush = true; // Should the robot strart driving when the button is pushed?
	bool released = true; // Has the button been released after a press?
};

#endif // _BUTTON_H_