#ifndef XBOX_CONTROLLER_HEADER_GUARD
#define XBOX_CONTROLLER_HEADER_GUARD

#include "WPILib.h"
#include "Vector2.h"
#include "PolarCoord.h"

class XBoxController {
private:
	Joystick *joystick;

	float leftStickXOffset;
	float leftStickYOffset;

	float rightStickXOffset;
	float rightStickYOffset;

	float leftTriggerOffset;
	float rightTriggerOffset;

	int leftStickXId;
	int leftStickYId;

	int rightStickXId;
	int rightStickYId;

	int leftTriggerId;
	int rightTriggerId;

	float leftTriggerButtonThreshold;
	float rightTriggerButtonThreshold;

public:
	/* Button Ids */
	int BUTTON_LEFT_STICK_CLICK;
	int BUTTON_RIGHT_STICK_CLICK;

	int BUTTON_LEFT_BUMPER;
	int BUTTON_RIGHT_BUMPER;

	int BUTTON_LEFT_TRIGGER;
	int BUTTON_RIGHT_TRIGGER;

	int BUTTON_A;
	int BUTTON_B;
	int BUTTON_X;
	int BUTTON_Y;

	int BUTTON_BACK;
	int BUTTON_START;

	int DPAD_UP;
	int DPAD_UP_RIGHT;
	int DPAD_RIGHT;
	int DPAD_DOWN_RIGHT;
	int DPAD_DOWN;
	int DPAD_DOWN_LEFT;
	int DPAD_LEFT;
	int DPAD_UP_LEFT;

	XBoxController(Joystick *joystick);
	XBoxController(XBoxController const&);

	void calibrate();

	bool getButton(int buttonId);
	bool getDPad(int DpadId);

	void rumbleLeft(float value);
	void rumbleRight(float value);

	Vector2 getStick(int xId, int yId, float xOffset, float yOffset);

	Vector2 getRightStickVector();
	Vector2 getLeftStickVector();

	PolarCoord getRightStickPolar();
	PolarCoord getLeftStickPolar();

	float getLeftTrigger();
	float getRightTrigger();
};

#endif
