#include "XBoxController.h"

/* Initialize Static Constants */


XBoxController::XBoxController(Joystick *joystick): joystick(joystick){
	/* Joysticks */
	leftStickXOffset = 0.5;
	leftStickYOffset = 0.5;

	rightStickXOffset = 0.5;
	rightStickYOffset = 0.5;

	leftTriggerOffset = 0.5;
	rightTriggerOffset = 0.5;

	leftStickXId = 0;
	leftStickYId = 1;

	rightStickXId = 4;
	rightStickYId = 5;

	rightTriggerId= 3;
	leftTriggerId = 2;

	leftTriggerButtonThreshold = 0.8;
	rightTriggerButtonThreshold = 0.8;

	/* Buttons */
	BUTTON_LEFT_STICK_CLICK = 9;
	BUTTON_RIGHT_STICK_CLICK = 10;

	BUTTON_LEFT_BUMPER = 5;
	BUTTON_RIGHT_BUMPER = 6;

	BUTTON_RIGHT_TRIGGER = -1;
	BUTTON_LEFT_TRIGGER = -2;

	BUTTON_A = 1;
	BUTTON_B = 2;
	BUTTON_X = 3;
	BUTTON_Y = 4;

	BUTTON_BACK = 7;
	BUTTON_START = 8;

	DPAD_UP = 0;
	DPAD_UP_RIGHT = 1;
	DPAD_RIGHT = 2;
	DPAD_DOWN_RIGHT = 3;
	DPAD_DOWN = 4;
	DPAD_DOWN_LEFT = 5;
	DPAD_LEFT = 6;
	DPAD_UP_LEFT = 7;
}

void XBoxController::calibrate(){
	Vector2 rawLeftStick = getStick(leftStickXId, leftStickYId, 0, 0);
	Vector2 rawRightStick = getStick(rightStickXId, rightStickYId, 0, 0);

	float rawLeftTrigger = joystick->GetRawAxis(leftTriggerId);
	float rawRightTrigger = joystick->GetRawAxis(rightTriggerId);

	leftStickXOffset = rawLeftStick.x;
	leftStickYOffset = rawLeftStick.y;

	rightStickXOffset = rawRightStick.x;
	rightStickYOffset = rawRightStick.y;

	leftTriggerOffset = rawLeftTrigger;
	rightTriggerOffset = rawRightTrigger;
}

bool XBoxController::getButton(int buttonId){
	if(buttonId == BUTTON_LEFT_TRIGGER){
		return getLeftTrigger() >= leftTriggerButtonThreshold;
	} else if(buttonId == BUTTON_RIGHT_TRIGGER){
		return getRightTrigger() >= rightTriggerButtonThreshold;
	} else {
		return joystick->GetRawButton(buttonId);
	}
}

bool XBoxController::getDPad(int DPadId){
	return joystick->GetPOV(DPadId);
}

void XBoxController::rumbleLeft(float value){
	joystick->SetRumble(Joystick::RumbleType::kLeftRumble, value);
}

void XBoxController::rumbleRight(float value){
	joystick->SetRumble(Joystick::RumbleType::kRightRumble, value);
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


/* Trigger */
float XBoxController::getLeftTrigger(){
	float rawValue = joystick->GetRawAxis(leftTriggerId);
	return (rawValue - leftTriggerOffset) * 2;
}

float XBoxController::getRightTrigger(){
	float rawValue = joystick->GetRawAxis(rightTriggerId);
	return (rawValue - rightTriggerOffset) * 2;
}

