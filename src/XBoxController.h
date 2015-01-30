#ifndef XBOX_CONTROLLER_HEADER_GUARD
#define XBOX_CONTROLLER_HEADER_GUARD

#include "WPILib.h"
#include "Vector2.h"
#include "PolarCoord.h"

class XBoxController {
private:
	Joystick joystick = XBoxController;

	const int leftStickXId = 1;
	const int leftStickYId = 2;

	const int rightStickXId = 4;
	const int rightStickYId = 5;

public:
	XBoxController(Joystick joystick);
	XBoxController(XBoxController const&);

	Vector2 getStick(int xId, int yId);

	Vector2 getRightStickVector();
	Vector2 getLeftStickVector();

	PolarCoord getRightStickPolar();
	PolarCoord getLeftStickPolar();
};

#endif
