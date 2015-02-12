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

	Joystick driverJoystick;
	Joystick clawJoystick;

	XBoxController *driverController;
	XBoxController *clawController;

	Victor *frontLeftDriveMotor;
	Victor *backLeftDriveMotor;
	Victor *frontRightDriveMotor;
	Victor *backRightDriveMotor;

	Victor *elevatorLeftMotor;
	Victor *elevatorRightMotor;

	Jaguar *armsLeftMotor;
	Jaguar *armsRightMotor;

	Jaguar *armsWheelLeftMotor;
	Jaguar *armsWheelRightMotor;

	RobotDrive *myRobot;

	float elevatorMotorSpeed = 0.8;
	float armsMotorSpeed = 0.15;
	float armsWheelMotorSpeed = 0.5;

	float driveLockModeValues[5] {0, 90, 180, 270, 360};

public:
	Robot():
		driverJoystick(0),
		clawJoystick(1),

		driverController(new XBoxController(&driverJoystick)),
		clawController(new XBoxController(&clawJoystick)),

		frontLeftDriveMotor(new Victor(0)),
		backLeftDriveMotor(new Victor(1)),
		frontRightDriveMotor(new Victor(2)),
		backRightDriveMotor(new Victor(3)),

		elevatorLeftMotor(new Victor(4)),
		elevatorRightMotor(new Victor(5)),

		armsLeftMotor(new Jaguar(6)),
		armsRightMotor(new Jaguar(7)),

		armsWheelLeftMotor(new Jaguar(8)),
		armsWheelRightMotor(new Jaguar(9)),

		myRobot(new RobotDrive(frontLeftDriveMotor, backLeftDriveMotor, frontRightDriveMotor, backRightDriveMotor))
	{
		myRobot->SetExpiration(0.1);
		myRobot->SetInvertedMotor(RobotDrive::MotorType::kFrontRightMotor, true);
		myRobot->SetInvertedMotor(RobotDrive::MotorType::kRearRightMotor, true);
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

		delete frontLeftDriveMotor;
		delete frontRightDriveMotor;
		delete backLeftDriveMotor;
		delete backRightDriveMotor;

		delete myRobot;
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

			//Vibrator Controller
			bool driverBackButton = driverController->getButton(driverController->BUTTON_BACK);
			bool clawBackButton = clawController->getButton(clawController->BUTTON_BACK);

			if(driverBackButton){
				driverController->rumbleLeft(1);
				driverController->rumbleRight(1);
			} else {
				driverController->rumbleLeft(0);
				driverController->rumbleRight(0);
			}

			if(clawBackButton){
				clawController->rumbleLeft(1);
				clawController->rumbleRight(1);
			} else {
				clawController->rumbleLeft(0);
				clawController->rumbleRight(0);
			}

			//Elevator control
			bool clawDPadUp = clawController->getDPad(clawController->DPAD_UP);
			bool clawDPadDown = clawController->getDPad(clawController->DPAD_DOWN);

			if(clawDPadUp){
				elevatorLeftMotor->Set(elevatorMotorSpeed);
				elevatorRightMotor->Set(elevatorMotorSpeed);
			} else if(clawDPadDown){
				elevatorLeftMotor->Set(-1 * elevatorMotorSpeed);
				elevatorRightMotor->Set(-1 * elevatorMotorSpeed);
			} else{
				elevatorLeftMotor->StopMotor();
				elevatorRightMotor->StopMotor();
			}

			//Arms control
			bool clawDPadLeft = clawController->getDPad(clawController->DPAD_LEFT);
			bool clawDPadRight = clawController->getDPad(clawController->DPAD_RIGHT);

			if(clawDPadLeft){
				armsLeftMotor->Set(-1 * armsMotorSpeed);
				armsRightMotor->Set(armsMotorSpeed);
			} else if(clawDPadRight){
				armsLeftMotor->Set(armsMotorSpeed);
				armsRightMotor->Set(-1 * armsMotorSpeed);
			} else{
				armsLeftMotor->StopMotor();
				armsRightMotor->StopMotor();
			}

			//Arms wheel control
			bool clawLeftBumper = clawController->getButton(clawController->BUTTON_LEFT_BUMPER);
			bool clawRightBumper = clawController->getButton(clawController->BUTTON_RIGHT_BUMPER);

			bool clawLeftTrigger = clawController->getButton(clawController->BUTTON_LEFT_TRIGGER);
			bool clawRightTrigger = clawController->getButton(clawController->BUTTON_RIGHT_TRIGGER);

			if(clawLeftBumper && !clawLeftTrigger){
				armsWheelLeftMotor->Set(armsWheelMotorSpeed);
			} else if(!clawLeftBumper && clawLeftTrigger){
				armsWheelLeftMotor->Set(-1 * armsWheelMotorSpeed);
			} else {
				armsWheelLeftMotor->Set(0);
			}

			if(clawRightBumper && !clawRightTrigger){
				armsWheelRightMotor->Set(armsWheelMotorSpeed);
			} else if(!clawRightBumper && clawRightTrigger){
				armsWheelRightMotor->Set(-1 * armsWheelMotorSpeed);
			} else {
				armsWheelRightMotor->Set(0);
			}

			//Drive robot
			PolarCoord driverLeftStick = driverController->getLeftStickPolar();

			float driveMagnitude = pow(driverLeftStick.magnitude, 2.0);
			float driveAngle = driverLeftStick.angle;
			float driveRotation = pow(driverController->getRightStickVector().x, 2);

			bool driverRightBumper = driverController->getButton(driverController->BUTTON_RIGHT_BUMPER);

			if(driverRightBumper){
				float driveLockModeDifs[5];

				int i = 0;
				for(float lockModeValue : driveLockModeValues){
					driveLockModeDifs[i] = abs(driverLeftStick.angle - lockModeValue);

					i++;
				}

				i = 0;
				int lowestDifIndex = 0;
				for(float lockModeDif : driveLockModeDifs){
					if(lockModeDif < driveLockModeDifs[lowestDifIndex]){
						lowestDifIndex = i;
					}

					i++;
				}

				driveAngle = driveLockModeValues[lowestDifIndex];
			}

			if(driverController->getRightStickVector().x < 0){
				driveRotation *= -1;
			}

			myRobot->MecanumDrive_Polar(driveMagnitude, driveAngle, driveRotation);
			//                              magnitude,  direction,      rotation

			Wait(0.005);//wait for a motor update time
		}
	}

};

START_ROBOT_CLASS(Robot);
