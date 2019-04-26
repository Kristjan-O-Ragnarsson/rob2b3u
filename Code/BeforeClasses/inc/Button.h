#ifndef _BUTTON_H_
#define _BUTTON_H_
/*
class Button {
public:
	void buttonLoop();
	void buttonSetup();
	void buttonDebugInfo(bool, bool, bool = true);

	void setRunning(bool);
	bool getRunning();

private:
	bool startOnPush = true;
	bool released = true;
	bool running = false;
};
*/

void buttonLoop();
void buttonSetup();
void buttonDebugInfo(bool, bool, bool = true);

void setRunning(bool);
bool getRunning();

#endif // _BUTTON_H_