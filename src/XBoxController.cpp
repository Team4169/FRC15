#include "XBoxController.h"

XBoxController::XBoxController(){}

void XBoxController::calibrate(Joystick *joystick){
	Vector2 rawLeftStick = getStick(leftStickXId, leftStickYId, 0, 0, joystick);
	Vector2 rawRightStick = getStick(rightStickXId, rightStickYId, 0, 0, joystick);

	leftStickXOffset = rawLeftStick.x;
	leftStickYOffset = rawLeftStick.y;

	rightStickXOffset = rawRightStick.x;
	rightStickYOffset = rawRightStick.y;
}

bool XBoxController::getButton(int buttonId, Joystick *joystick){
	return joystick->GetRawButton(buttonId);
}

/* Vector */
Vector2 XBoxController::getStick(int xId, int yId, float xOffset, float yOffset, Joystick *joystick){
	float x = joystick->GetRawAxis(xId) - xOffset;
	float y = joystick->GetRawAxis(yId) - yOffset;

	return Vector2(x, y);
}

Vector2 XBoxController::getLeftStickVector(Joystick *joystick){
	return getStick(leftStickXId, leftStickYId, leftStickXOffset, leftStickYOffset, joystick);
}

Vector2 XBoxController::getRightStickVector(Joystick *joystick){
	return getStick(rightStickXId, rightStickYId, rightStickXOffset, rightStickYOffset, joystick);
}

/* Polar */
PolarCoord XBoxController::getRightStickPolar(Joystick *joystick){
	return PolarCoord(getRightStickVector(joystick));
}

PolarCoord XBoxController::getLeftStickPolar(Joystick *joystick){
	return PolarCoord(getLeftStickVector(joystick));
}


