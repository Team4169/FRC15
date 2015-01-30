#ifndef XBOX_CONTROLLER_HEADER_GUARD
#define XBOX_CONTROLLER_HEADER_GUARD

#include "WPILib.h"
#include "Vector2.h"
#include "PolarCoord.h"

class XBoxController {
private:
	float leftStickXOffset = 0.5;
	float leftStickYOffset = 0.5;

	float rightStickXOffset = 0.5;
	float rightStickYOffset = 0.5;

	int leftStickXId = 1;
	int leftStickYId = 2;

	int rightStickXId = 4;
	int rightStickYId = 5;

public:
	/* Button Ids */
	static int BUTTON_LEFT_STICK_CLICK = 9;
	static int BUTTON_RIGHT_STICK_CLICK = 10;

	static int BUTTON_LEFT_BUMPER = 5;
	static int BUTTON_RIGHT_BUMPER = 6;

	static int BUTTON_A = 1;
	static int BUTTON_B = 2;
	static int BUTTON_X = 3;
	static int BUTTON_Y = 4;

	static int BUTTON_BACK = 7;
	static int BUTTON_START = 8;

	XBoxController();
	XBoxController(XBoxController const&);

	void calibrate(Joystick *joystick);

	bool getButton(int buttonId, Joystick *joystick);
	Vector2 getStick(int xId, int yId, float xOffset, float yOffset, Joystick *joystick);

	Vector2 getRightStickVector(Joystick *joystick);
	Vector2 getLeftStickVector(Joystick *joystick);

	PolarCoord getRightStickPolar(Joystick *joystick);
	PolarCoord getLeftStickPolar(Joystick *joystick);
};

#endif
