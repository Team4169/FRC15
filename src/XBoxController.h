#ifndef XBOX_CONTROLLER_HEADER_GUARD
#define XBOX_CONTROLLER_HEADER_GUARD

#include "WPILib.h"
#include "Vector2.h"
#include "PolarCoord.h"

class XBoxController {
private:
	int leftStickXId = 1;
	int leftStickYId = 2;

	int rightStickXId = 4;
	int rightStickYId = 5;

public:
	XBoxController();
	XBoxController(XBoxController const&);

	Vector2 getStick(int xId, int yId, Joystick *joystick);

	Vector2 getRightStickVector(Joystick *joystick);
	Vector2 getLeftStickVector(Joystick *joystick);

	PolarCoord getRightStickPolar(Joystick *joystick);
	PolarCoord getLeftStickPolar(Joystick *joystick);
};

#endif
