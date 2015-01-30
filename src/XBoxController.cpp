#include "XBoxController.h"

XBoxController::XBoxController(){}

/* Vector */
Vector2 XBoxController::getStick(int xId, int yId, Joystick *joystick){
	float x = joystick->GetRawAxis(xId);
	float y = joystick->GetRawAxis(yId);

	return Vector2(x, y);
}

Vector2 XBoxController::getLeftStickVector(Joystick *joystick){
	return getStick(leftStickXId, leftStickYId, joystick);
}

Vector2 XBoxController::getRightStickVector(Joystick *joystick){
	return getStick(rightStickXId, rightStickYId, joystick);
}

/* Polar */
PolarCoord XBoxController::getRightStickPolar(Joystick *joystick){
	return PolarCoord(getRightStickVector(joystick));
}

PolarCoord XBoxController::getLeftStickPolar(Joystick *joystick){
	return PolarCoord(getLeftStickVector(joystick));
}


