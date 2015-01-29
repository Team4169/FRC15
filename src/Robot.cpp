#include "WPILib.h"
#include "XBoxController.h"

class Robot: public SampleRobot {
	RobotDrive myRobot;

	Joystick driverJoystick;
	XBoxController driverController;

public:
	Robot():
		myRobot(0, 1, 2, 3),
		driverJoystick(0),
		driverController(XBoxController(driverJoystick)) {
		myRobot.SetExpiration(0.1);
	}

	void OperatorControl(){
		while (IsOperatorControl() && IsEnabled()){
			PolarCoord driverLeftStick = driverController.getLeftStickPolar();
			PolarCoord driverRightStick = driverController.getRightStickPolar();

			myRobot.MecanumDrive_Polar(driverLeftStick.magnitude,
					driverLeftStick.angle,
					driverRightStick.angle);//magnitude, direction, rotation
			Wait(0.005);//wait for a motor update time
		}
	}

};

START_ROBOT_CLASS(Robot);
