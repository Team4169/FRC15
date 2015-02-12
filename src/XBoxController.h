#ifndef XBOX_CONTROLLER_HEADER_GUARD
#define XBOX_CONTROLLER_HEADER_GUARD

#include "WPILib.h"
#include "Vector2.h"
#include "PolarCoord.h"

/**
 * A class to help get input from a controller.
 * The values are currently configured for an XBox controllers. However the constants are
 * member variables so they can be overridden for different controllers.
 */
class XBoxController {
private:
	Joystick *joystick;///The WPILib Joystick to get input from

	/**
	 * The offset for the left stick x axis on the controller. This is needed
	 * because the resting value is 0.5f. To account for this we subtract the offset
	 * to fix this. The controller values can also drift over the course of operation.
	 */
	float leftStickXOffset;
	float leftStickYOffset;/// See leftStickYOffset

	float rightStickXOffset;/// See leftStickXOffset
	float rightStickYOffset;/// see leftStickXOffset

	/**
	 * Similar to leftStickXOffset, however this if for the triggers
	 * The triggers are treated like a single axis
	 */
	float leftTriggerOffset;
	float rightTriggerOffset;/// See leftTriggerOffset

	int leftStickXId;/// The raw axis id of the left stick x axis
	int leftStickYId;/// The raw axis id of the left stick y axis

	int rightStickXId;/// The raw axis id of the right stick x axis
	int rightStickYId;/// The raw axis id of the right stick y axis

	int leftTriggerId;/// The raw axis id of the left trigger, which is treated like an axis
	int rightTriggerId;/// The raw axis id of the right trigger, which is treated like an axis

	/**
	 * The value the left trigger has to pass to be considered pressed when fetched as a button
	 */
	float leftTriggerButtonThreshold;
	float rightTriggerButtonThreshold;/// Same as the leftTriggerButtonThreshold but for the right trigger

public:
	/* Button Ids */
	int BUTTON_LEFT_STICK_CLICK;
	int BUTTON_RIGHT_STICK_CLICK;

	int BUTTON_LEFT_BUMPER;
	int BUTTON_RIGHT_BUMPER;

	int BUTTON_LEFT_TRIGGER;
	int BUTTON_RIGHT_TRIGGER;

	int BUTTON_A;
	int BUTTON_B;
	int BUTTON_X;
	int BUTTON_Y;

	int BUTTON_BACK;
	int BUTTON_START;

	int DPAD_UP;
	int DPAD_UP_RIGHT;
	int DPAD_RIGHT;
	int DPAD_DOWN_RIGHT;
	int DPAD_DOWN;
	int DPAD_DOWN_LEFT;
	int DPAD_LEFT;
	int DPAD_UP_LEFT;

	XBoxController(Joystick *joystick);
	XBoxController(XBoxController const&);

	void calibrate();

	bool getButton(int buttonId);
	bool getDPad(int DpadId);

	void rumbleLeft(float value);
	void rumbleRight(float value);

	Vector2 getStick(int xId, int yId, float xOffset, float yOffset);

	Vector2 getRightStickVector();
	Vector2 getLeftStickVector();

	PolarCoord getRightStickPolar();
	PolarCoord getLeftStickPolar();

	float getLeftTrigger();
	float getRightTrigger();
};

#endif
