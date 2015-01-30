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

	int leftStickXId;
	int leftStickYId;

	int rightStickXId;
	int rightStickYId;

public:
	/* Button Ids */
	int BUTTON_LEFT_STICK_CLICK;
	int BUTTON_RIGHT_STICK_CLICK;

	int BUTTON_LEFT_BUMPER;
	int BUTTON_RIGHT_BUMPER;

	int BUTTON_A;
	int BUTTON_B;
	int BUTTON_X;
	int BUTTON_Y;

	int BUTTON_BACK;
	int BUTTON_START;

	XBoxController(Joystick *joystick);
	XBoxController(XBoxController const&);

	void calibrate();

	bool getButton(int buttonId);
	Vector2 getStick(int xId, int yId, float xOffset, float yOffset);

	Vector2 getRightStickVector();
	Vector2 getLeftStickVector();

	PolarCoord getRightStickPolar();
	PolarCoord getLeftStickPolar();
};

#endif
