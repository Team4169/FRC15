#include "WPILib.h"
#include "XBoxController.h"

#include <iostream>
#include <math.h>

class Robot: public SampleRobot {
	/**
	 * Motor Ports
	 * 		0-3 Drive Motors
	 * 			0, 1 - Left drive motors
	 * 			2, 3 - Right drive motors
	 *
	 * 		4-5 Elevator Motors
	 * 			4    - Left elevator motor
	 * 			5    - Right elevator motor
	 *
	 * 		6-7 Arms Motors
	 * 			6    - Left arm motor
	 * 			7    - Right arm motors
	 * 		8-9
	 * 			8    - Left arm wheel motor
	 * 			9    - Right arm wheel motor
	 */

	RobotDrive myRobot;

	Joystick driverJoystick;
	XBoxController *driverController;

	Joystick clawJoystick;
	XBoxController *clawController;

	Victor *elevatorLeftMotor;
	Victor *elevatorRightMotor;

	Jaguar *armsLeftMotor;
	Jaguar *armsRightMotor;

	Jaguar *armsWheelLeftMotor;
	Jaguar *armsWheelRightMotor;

	float elevatorMotorSpeed = 0.8;
	float armsMotorSpeed = 0.15;
	float armsWheelMotorSpeed = 0.5;

public:
	Robot():
		myRobot(0, 1, 2, 3),

		driverJoystick(0),
		clawJoystick(1),

		driverController(new XBoxController(&driverJoystick)),
		clawController(new XBoxController(&clawJoystick)),

		elevatorLeftMotor(new Victor(4)),
		elevatorRightMotor(new Victor(5)),

		armsLeftMotor(new Jaguar(6)),
		armsRightMotor(new Jaguar(7)),

		armsWheelLeftMotor(new Jaguar(8)),
		armsWheelRightMotor(new Jaguar(9))
	{
		myRobot.SetExpiration(0.1);
		myRobot.SetInvertedMotor(RobotDrive::MotorType::kFrontRightMotor, true);
		myRobot.SetInvertedMotor(RobotDrive::MotorType::kRearRightMotor, true);
	}

	~Robot(){
		delete driverController;
		delete clawController;

		delete elevatorLeftMotor;
		delete elevatorRightMotor;

		delete armsLeftMotor;
		delete armsRightMotor;

		delete armsWheelLeftMotor;
		delete armsWheelRightMotor;
	}

	void OperatorControl(){
		driverController->calibrate();//Calibrate initially

		while (IsOperatorControl() && IsEnabled()){

			//Recalibrate if the Start button is pressed
			if(driverController->getButton(driverController->BUTTON_START)){
				driverController->calibrate();
			}

			if(clawController->getButton(clawController->BUTTON_START)){
				clawController->calibrate();
			}

			//Elevator control
			bool driverYButton = driverController->getButton(driverController->BUTTON_Y);
			bool driverAButton = driverController->getButton(driverController->BUTTON_A);

			bool driverLeftTrigger = driverController->getButton(driverController->BUTTON_LEFT_BUMPER);
			bool driverRightTrigger = driverController->getButton(driverController->BUTTON_RIGHT_BUMPER);

			if(driverYButton && !driverLeftTrigger && !driverRightTrigger){//All up
				elevatorLeftMotor->Set(elevatorMotorSpeed);
				elevatorRightMotor->Set(elevatorMotorSpeed);
			} else if(driverAButton && !driverLeftTrigger && !driverRightTrigger){//All down
				elevatorLeftMotor->Set(-1 * elevatorMotorSpeed);
				elevatorRightMotor->Set(-1 * elevatorMotorSpeed);
			} else if(driverYButton && driverLeftTrigger && !driverRightTrigger){//Left up
				elevatorLeftMotor->Set(elevatorMotorSpeed);
				elevatorRightMotor->Set(0);
			} else if(driverYButton && !driverLeftTrigger && driverRightTrigger){//Right up
				elevatorLeftMotor->Set(0);
				elevatorRightMotor->Set(elevatorMotorSpeed);
			} else if(driverAButton && driverLeftTrigger && !driverRightTrigger){//Left down
				elevatorLeftMotor->Set(-1 * elevatorMotorSpeed);
				elevatorRightMotor->Set(0);
			} else if(driverAButton && !driverLeftTrigger && driverRightTrigger){//Right down
				elevatorLeftMotor->Set(0);
				elevatorRightMotor->Set(-1 * elevatorMotorSpeed);
			} else {//Nothing
				elevatorLeftMotor->Set(0);
				elevatorRightMotor->Set(0);
			}

			//Arms control
			bool driverXButton = driverController->getButton(driverController->BUTTON_X);
			bool driverBButton = driverController->getButton(driverController->BUTTON_B);

			if(driverXButton){
				armsRightMotor->Set(-1 * armsMotorSpeed);
				armsLeftMotor->Set(armsMotorSpeed);
			} else if(driverBButton){
				armsRightMotor->Set(armsMotorSpeed);
				armsLeftMotor->Set(-1 * armsMotorSpeed);
			} else {
				armsRightMotor->StopMotor();
				armsLeftMotor->StopMotor();
			}


			//Drive robot
			PolarCoord driverLeftStick = driverController->getLeftStickPolar();
			PolarCoord driverRightStick = driverController->getRightStickPolar();

			printf("Left Stick (%f, %f), Right Stick (%f, %f)\n",
					driverLeftStick.magnitude, driverLeftStick.angle.angle,
					driverRightStick.magnitude, driverRightStick.angle.angle);

			myRobot.MecanumDrive_Polar(pow(driverLeftStick.magnitude, 2.0),
					driverLeftStick.angle,
					driverController->getRightStickVector().x);//magnitude, direction, rotation
			//myRobot.MecanumDrive_Polar(0,0,0);
			Wait(0.005);//wait for a motor update time
		}
	}

};

START_ROBOT_CLASS(Robot);
