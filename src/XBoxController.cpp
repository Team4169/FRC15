#include "XBoxController.h"

XBoxController::XBoxController(Joystick joystick): joystick(joystick){}

/* Vector */
Vector2 XBoxController::getStick(int xId, int yId){
	float x = joystick.GetRawAxis(xId);
	float y = joystick.GetRawAxis(yId);

	return Vector2::Vector2(x, y);
}

Vector2 XBoxController::getLeftStickVector(){
	return getStick(leftStickXId, leftStickYId);
}

Vector2 XBoxController::getRightStickVector(){
	return getStick(rightStickXId, rightStickYId);
}

/* Polar */
PolarCoord XBoxController::getRightStickPolar(){
	return getRightStickVector();
}

PolarCoord XBoxController::getLeftStickPolar(){
	return getLeftStickVector();
}


