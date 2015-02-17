#ifndef FRC15_XBOX_CONTROLLER_H
#define FRC15_XBOX_CONTROLLER_H

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
	Joystick *mJoystick;///< The WPILib Joystick to get input from

    /** @defgroup Axis offsets
    * Each axis on the XBox controller starts half engaged. The range is 0f-1f, when retrieving the raw axis value
    * in a neutral state the value will usually be around 0.5f. To compensate for this an offset is applied to the value.
    * This makes it so at a neutral position the axis will return 0.0f.
    *
    * The axis offsets can also be re-calibrated during use to compensate for bad axis sensors. This helps address issues
    * with wandering values.
    * @{
    */
	float mLeftStickXOffset;///< Left stick x axis offset
	float mLeftStickYOffset;///< Left stick y axis offset

	float mRightStickXOffset;///< Right stick x axis offset
	float mRightStickYOffset;///< Right stick y axis offset

    /** @defgroup Trigger axis offsets
    * The triggers on a XBox controller a treated like axises. Their values range from 0f-1f and start at 0.5f similar to
    * Joystick axises. To retrieve trigger values, similar to joystick axises, you use the Joystick->GetRawAxis method
    *
    * This is because the triggers are actually hooked up to potentiometer that measures how pressed down they are.
    * @{
    */
	float mLeftTriggerOffset;///< Left trigger axis offset
	float mRightTriggerOffset;///< Right trigger axis offset
    /** @} */
    /** @} */

    /** @defgroup Axis ids
    * To retrieve values from axises you must call a method on the WIP Joystick called GetRawAxis. This method takes a
    * axis id. The following are the axis ids for the XBox controller.
    * @{
    */
	int mLeftStickXId;///< Left stick x axis id
	int mLeftStickYId;///< Left stick y axis id

	int mRightStickXId;///< Right stick x axis id
	int mRightStickYId;///< Right stick y axis id

    /** @defgroup Trigger axis ids
    * Triggers are treated as axises, to get their values you must use the same technique as is used to get joystick
    * axises.
    * @{
    */
	int mLeftTriggerId;///< Left trigger axis id
	int mRightTriggerId;///< Right trigger axis id
    /** @}
    /** @} */

    /** @defgroup Trigger button thresholds
	* Using the @see XBoxController class the triggers can be treated as an axis, or as a button. The triggers are
    * inherently axises, to make them act as buttons the @see XBoxController class checks to see if trigger axis value
    * is over a certain threshold.
    * @{
    */
	float mLeftTriggerButtonThreshold;///< Left trigger button pressed threshold
	float mRightTriggerButtonThreshold;///< Right trigger button pressed threshold
    /** @} */

public:
    /** @defgroup Button ids
    * To get button states on a controller you must use the method from the WPI Joystick object called getButton(). This
    * method takes a button id.
	* @{
    */

    /** @defgroup Joystick click buttons
    * The joysticks on an XBox controller can be pushed down. This will be read as a button press.
    * @{
    */
	int BUTTON_LEFT_STICK_CLICK;///< Left stick click button id
	int BUTTON_RIGHT_STICK_CLICK;///< Right stick click button id
    /** @} */

	int BUTTON_LEFT_BUMPER;///< Left bumper button id
	int BUTTON_RIGHT_BUMPER;///< Right bumper button id

    /** @defgroup Trigger button ids
    * The trigger button ids are actually not fed into the Joystick->getButton() method. Instead the
    * @see XBoxController::getButton() checks to see if a trigger button id is fed in. If a trigger button id is fed in
    * as a button id then it will preform a check against the appropriate trigger button threshold and return a value
    * accordingly.
    *
    * To prevent overlap with real button ids negative values are used as trigger button ids
    * @{
    */
	int BUTTON_LEFT_TRIGGER;///< Left trigger button id
	int BUTTON_RIGHT_TRIGGER;///< Right trigger button id
    /** @} */

	int BUTTON_A;///< A button id
	int BUTTON_B;///< B button id
	int BUTTON_X;/// X button id
	int BUTTON_Y;/// Y button id

	int BUTTON_BACK;///< Back button id
	int BUTTON_START;///< Start button id
    /** @} */

    /** @defgroup DPad button ids
    * The DPad is officially called the POV by FRC and windows. The DPad has 8 positions, starting at north, and
    * incrementing by 45 degrees. To get a position state you need to provide a DPad position id similar to getting a
    * button. The method called is Joystick->GetPov().
    * @{
    */
	float DPAD_UP;///< DPad north(0 deg) position id
	float DPAD_UP_RIGHT;///< DPad north east(45 deg) position id
	float DPAD_RIGHT;///< DPad east(90 deg) position id
	float DPAD_DOWN_RIGHT;///< DPad south east(135 deg) position id
	float DPAD_DOWN;///< DPad south(180 deg) position id
	float DPAD_DOWN_LEFT;///< DPad south west(225 deg) position id
	float DPAD_LEFT;///< DPad west(270 deg) position id
	float DPAD_UP_LEFT;/// DPad north west(315 deg) position id
    /** @} */

    /**
    * The default XBoxController constructor.
    * @param joystick The WPI Joystick to get values from
    */
	XBoxController(Joystick *joystick);

    /**
    * A C++ 03 compatibility constructor, this is never used and is just defined to fix errors
    * See <a href="https://github.com/Team4169/FRC15/issues/1">the Github issue</a> for more information
    */
	XBoxController(XBoxController const&);

	/**
	 * Class deconstructor, releases pointer for joystick
	 */
	~XBoxController();

    /**
    * @brief Calibrate the axis offsets.
    * Takes all axises and gets their values, this assumes that they are in their neutral position. It then takes all
    * these axis values and sets the appropriate axis offset to the related axis value. This ensures that when the axis
    * is in a neutral position the value is 0f, not 0.5f.
    *
    * If any of the axises are not in their neutral position(Untouched) then their current position will be recorded as
    * their center point. This can mess up the values significantly, so make sure to tell your drives not to press
    * forward on the axises when they are being calibrated.
    */
	void Calibrate();

    /**
    * @brief Gets the specified button
    * Gets the specified button id. If the button id is a trigger button id then the method will act in the following
    * manner:
    *
    * If the trigger axis value is under the appropriate trigger button threshold it will be treated as an unpressed
    * button. If the trigger axis value is over or equal to the appropriate trigger button threshold then it will be
    * treated as a pressed button.
    *
    * @param buttonId The button id of the requested button
    * @return true if the button is pressed, and false if the button is not
    */
	bool GetButton(int buttonId);

    /**
    * Gets the specified DPad direction
    * @param DpadId The id of the DPad direction
    * @return true if the DPad direction is pressed, and false if it is not
    */
	bool GetDPad(int DpadId);

    /** @defgroup Rumble motors
    * Starts the left rumble motor on the controller.
    * Note: The rumble motor will stay at the value set until you tell it otherwise. So if set the rumble value to 1
    * at the start of a program, the rumble motor will keep rumbling for the duration of the program.
    *
    * @param value The power of the rumble on a scale from 0f-1f
    * @{
    */
	void RumbleLeft(float value);///< Starts the left rumble motor
	void RumbleRight(float value);///< Starts the right rumble motor
    /** @} */

    /**
    * @brief Gets the value of a joystick on the controller
    * This method converts two axises into a @see Vector2 value. Inside this method the axis offsets are applied to the
    * Vector2 value. This is the base of all the other methods for getting the right and left joysticks on the controller.
    *
    * @param xId The x axis id of the joystick
    * @param yId The y axis id of the joystick
    * @param xOffset The x axis offset for the joystick
    * @param yOffset The y axis offset for the joystick
    *
    * @return A Vector2 of the joystick value(x, y) with the offsets applied
    */
	Vector2 GetStick(int xId, int yId, float xOffset, float yOffset);

	/** @defgroup Get controller joystick values
	 * @{
	 */
	Vector2 GetRightStickVector();
	Vector2 GetLeftStickVector();

	PolarCoord GetRightStickPolar();
	PolarCoord GetLeftStickPolar();
	/** @} */

	float GetLeftTrigger();
	float GetRightTrigger();
};

#endif
