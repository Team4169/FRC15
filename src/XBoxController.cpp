#include "XBoxController.h"

/* Initialize Static Constants */


XBoxController::XBoxController(Joystick *joystick): joystick(joystick){
	/* Joysticks */
	leftStickXOffset = 0.5;
	leftStickYOffset = 0.5;

	rightStickXOffset = 0.5;
	rightStickYOffset = 0.5;

	leftStickXId = 0;
	leftStickYId = 1;

	rightStickXId = 4;
	rightStickYId = 5;

	/* Buttons */
	BUTTON_LEFT_STICK_CLICK = 9;
	BUTTON_RIGHT_STICK_CLICK = 10;

	BUTTON_LEFT_BUMPER = 5;
	BUTTON_RIGHT_BUMPER = 6;

	BUTTON_A = 1;
	BUTTON_B = 2;
	BUTTON_X = 3;
	BUTTON_Y = 4;

	BUTTON_BACK = 7;
	BUTTON_START = 8;
}

void XBoxController::calibrate(){
	Vector2 rawLeftStick = getStick(leftStickXId, leftStickYId, 0, 0);
	Vector2 rawRightStick = getStick(rightStickXId, rightStickYId, 0, 0);

	leftStickXOffset = rawLeftStick.x;
	leftStickYOffset = rawLeftStick.y;

	rightStickXOffset = rawRightStick.x;
	rightStickYOffset = rawRightStick.y;
}

bool XBoxController::getButton(int buttonId){
	return joystick->GetRawButton(buttonId);
}

/* Vector */
Vector2 XBoxController::getStick(int xId, int yId, float xOffset, float yOffset){
	float x = joystick->GetRawAxis(xId) - xOffset;
	float y = joystick->GetRawAxis(yId) - yOffset;

	return Vector2(x, y);
}

Vector2 XBoxController::getLeftStickVector(){
	return getStick(leftStickXId, leftStickYId, leftStickXOffset, leftStickYOffset);
}

Vector2 XBoxController::getRightStickVector(){
	return getStick(rightStickXId, rightStickYId, rightStickXOffset, rightStickYOffset);
}

/* Polar */
PolarCoord XBoxController::getRightStickPolar(){
	return PolarCoord(getRightStickVector());
}

PolarCoord XBoxController::getLeftStickPolar(){
	return PolarCoord(getLeftStickVector());
}


