#include "WPILib.h"
#include "XBoxController.h"

#include <iostream>

class Robot: public SampleRobot {

	RobotDrive myRobot;

	Joystick driverJoystick;
	XBoxController *driverController;

	Victor *elevatorLeftMotor;
	Victor *elevatorRightMotor;

public:
	Robot():
		myRobot(0, 1, 2, 3),
		driverJoystick(0),
		driverController(new XBoxController(&driverJoystick)),
		elevatorLeftMotor(new Victor(4)),
		elevatorRightMotor(new Victor(5)){
		myRobot.SetExpiration(0.1);
	}

	~Robot(){
		delete driverController;
	}

	void OperatorControl(){
		driverController->calibrate();//Calibrate initially

		while (IsOperatorControl() && IsEnabled()){

			//Recalibrate if the Start button is pressed
			if(driverController->getButton(driverController->BUTTON_START)){
				driverController->calibrate();
			}

			//Elevator control
			bool driverYButton = driverController->getButton(driverController->BUTTON_Y);
			bool driverAButton = driverController->getButton(driverController->BUTTON_A);

			bool driverLeftTrigger = driverController->getButton(driverController->BUTTON_LEFT_BUMPER);
			bool driverRightTrigger = driverController->getButton(driverController->BUTTON_RIGHT_BUMPER);

			if(driverYButton && !driverLeftTrigger && !driverRightTrigger){//All up
				elevatorLeftMotor->Set(0.2);
				elevatorRightMotor->Set(0.2);
			} else if(driverAButton && !driverLeftTrigger && !driverRightTrigger){//All down
				elevatorLeftMotor->Set(-0.2);
				elevatorRightMotor->Set(-0.2);
			} else if(driverYButton && driverLeftTrigger && !driverRightTrigger){//Left up
				elevatorLeftMotor->Set(0.2);
				elevatorRightMotor->Set(0);
			} else if(driverYButton && !driverLeftTrigger && driverRightTrigger){//Right up
				elevatorLeftMotor->Set(0);
				elevatorRightMotor->Set(0.2);
			} else if(driverAButton && driverLeftTrigger && !driverRightTrigger){//Left down
				elevatorLeftMotor->Set(-0.2);
				elevatorRightMotor->Set(0);
			} else if(driverAButton && !driverLeftTrigger && driverRightTrigger){//Right down
				elevatorLeftMotor->Set(0);
				elevatorRightMotor->Set(-0.2);
			} else {//Nothing
				elevatorLeftMotor->Set(0);
				elevatorRightMotor->Set(0);
			}


			//Drive robot
			PolarCoord driverLeftStick = driverController->getLeftStickPolar();
			PolarCoord driverRightStick = driverController->getRightStickPolar();

			fprintf(stdout, "Left Stick (%f, %f), Right Stick (%f, %f)",
					driverLeftStick.magnitude, driverLeftStick.angle.angle,
					driverRightStick.magnitude, driverRightStick.angle.angle);

			myRobot.MecanumDrive_Polar(driverLeftStick.magnitude,
					driverLeftStick.angle,
					driverRightStick.angle);//magnitude, direction, rotation
			Wait(0.005);//wait for a motor update time
		}
	}

};

START_ROBOT_CLASS(Robot);
