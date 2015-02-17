#include "XBoxController.h"

XBoxController::XBoxController(Joystick *joystick): mJoystick(joystick){
	/* Joysticks */
	mLeftStickXOffset = 0.5;
	mLeftStickYOffset = 0.5;

	mRightStickXOffset = 0.5;
	mRightStickYOffset = 0.5;

	mLeftTriggerOffset = 0.5;
	mRightTriggerOffset = 0.5;

	mLeftStickXId = 0;
	mLeftStickYId = 1;

	mRightStickXId = 4;
	mRightStickYId = 5;

	mRightTriggerId= 3;
	mLeftTriggerId = 2;

	mLeftTriggerButtonThreshold = 0.8;
	mRightTriggerButtonThreshold = 0.8;

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
	DPAD_UP_RIGHT = 45;
	DPAD_RIGHT = 90;
	DPAD_DOWN_RIGHT = 135;
	DPAD_DOWN = 180;
	DPAD_DOWN_LEFT = 225;
	DPAD_LEFT = 270;
	DPAD_UP_LEFT = 315;
}

XBoxController::~XBoxController(){
	delete mJoystick;
}

void XBoxController::Calibrate(){
	Vector2 rawLeftStick = GetStick(mLeftStickXId, mLeftStickYId, 0, 0);
	Vector2 rawRightStick = GetStick(mRightStickXId, mRightStickYId, 0, 0);

	float rawLeftTrigger = mJoystick->GetRawAxis(mLeftTriggerId);
	float rawRightTrigger = mJoystick->GetRawAxis(mRightTriggerId);

	mLeftStickXOffset = rawLeftStick.x;
	mLeftStickYOffset = rawLeftStick.y;

	mRightStickXOffset = rawRightStick.x;
	mRightStickYOffset = rawRightStick.y;

	mLeftTriggerOffset = rawLeftTrigger;
	mRightTriggerOffset = rawRightTrigger;
}

bool XBoxController::GetButton(int buttonId){
	if(buttonId == BUTTON_LEFT_TRIGGER){
		return GetLeftTrigger() >= mLeftTriggerButtonThreshold;
	} else if(buttonId == BUTTON_RIGHT_TRIGGER){
		return GetRightTrigger() >= mRightTriggerButtonThreshold;
	} else {
		return mJoystick->GetRawButton(buttonId);
	}
}

bool XBoxController::GetDPad(int DPadId){
	return DPadId == mJoystick->GetPOV();
}

void XBoxController::RumbleLeft(float value){
	mJoystick->SetRumble(Joystick::RumbleType::kLeftRumble, value);
}

void XBoxController::RumbleRight(float value){
	mJoystick->SetRumble(Joystick::RumbleType::kRightRumble, value);
}

/* Vector */
Vector2 XBoxController::GetStick(int xId, int yId, float xOffset, float yOffset){
	float x = mJoystick->GetRawAxis(xId) - xOffset;
	float y = mJoystick->GetRawAxis(yId) - yOffset;

	return Vector2(x, y);
}

Vector2 XBoxController::GetLeftStickVector(){
	return GetStick(mLeftStickXId, mLeftStickYId, mLeftStickXOffset, mLeftStickYOffset);
}

Vector2 XBoxController::GetRightStickVector(){
	return GetStick(mRightStickXId, mRightStickYId, mRightStickXOffset, mRightStickYOffset);
}


/* Polar */
PolarCoord XBoxController::GetRightStickPolar(){
	return PolarCoord(GetRightStickVector());
}

PolarCoord XBoxController::GetLeftStickPolar(){
	return PolarCoord(GetLeftStickVector());
}


/* Trigger */
float XBoxController::GetLeftTrigger(){
	float rawValue = mJoystick->GetRawAxis(mLeftTriggerId);
	return (rawValue - mLeftTriggerOffset) * 2;
}

float XBoxController::GetRightTrigger(){
	float rawValue = mJoystick->GetRawAxis(mRightTriggerId);
	return (rawValue - mRightTriggerOffset) * 2;
}

