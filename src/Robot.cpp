#include "WPILib.h"
#include "XBoxController.h"

#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

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

	USBCamera mClawCamera;

	Joystick mDriverJoystick;
	Joystick mClawJoystick;

	XBoxController mDriverController;
	XBoxController mClawController;

	Victor mFrontLeftDriveMotor;
	Victor mBackLeftDriveMotor;
	Victor mFrontRightDriveMotor;
	Victor mBackRightDriveMotor;

	Victor mElevatorLeftMotor;
	Victor mElevatorRightMotor;

	Jaguar mArmsLeftMotor;
	Jaguar mArmsRightMotor;

	Jaguar mArmsWheelLeftMotor;
	Jaguar mArmsWheelRightMotor;

	DigitalInput mUpperElevatorLimitSwitch;
	DigitalInput mLowerElevatorLimitSwitch;

	RobotDrive mMyRobot;

	float kElevatorMotorSpeed = 0.8;
	float kArmsMotorSpeed = 0.15;
	float kArmsWheelMotorSpeed = 0.25;

	float kDriveLockModeValues[5] {0, 90, 180, 270, 360};


public:
	Robot():
		mClawCamera(USBCamera::kDefaultCameraName, false),

		mDriverJoystick(0),
		mClawJoystick(1),

		mDriverController(&mDriverJoystick),
		mClawController(&mClawJoystick),

		mFrontLeftDriveMotor(0),
		mBackLeftDriveMotor(1),
		mFrontRightDriveMotor(2),
		mBackRightDriveMotor(3),

		mElevatorLeftMotor(4),
		mElevatorRightMotor(5),

		mArmsLeftMotor(6),
		mArmsRightMotor(7),

		mArmsWheelLeftMotor(8),
		mArmsWheelRightMotor(9),

		mUpperElevatorLimitSwitch(0),
		mLowerElevatorLimitSwitch(1),

		mMyRobot(mFrontLeftDriveMotor, mBackLeftDriveMotor, mFrontRightDriveMotor, mBackRightDriveMotor)
	{
		mMyRobot.SetExpiration(0.1);
		mMyRobot.SetInvertedMotor(RobotDrive::MotorType::kFrontRightMotor, true);
		mMyRobot.SetInvertedMotor(RobotDrive::MotorType::kRearRightMotor, true);

		//mClawCamera.SetBrightness(10);

		//CameraServer::GetInstance()->SetQuality(100);
		//CameraServer::GetInstance()->StartAutomaticCapture(make_shared<USBCamera>(&mClawCamera));
		CameraServer::GetInstance()->StartAutomaticCapture();
	}

	~Robot(){}

	/* Physical Mechanism Helper Methods */
	//Elevator
	void MoveElevator(float motorSpeed){
		mElevatorLeftMotor.Set(-1 * motorSpeed);
		mElevatorRightMotor.Set(motorSpeed);
	}

	bool ElevatorSafeToMove(float dir){
		if(dir > 0){
			return !mUpperElevatorLimitSwitch.Get();
		} else if(dir < 0){
			return !mLowerElevatorLimitSwitch.Get();
		} else {
			return !mUpperElevatorLimitSwitch.Get() && !mLowerElevatorLimitSwitch.Get();
		}
	}

	void MoveElevatorSafeOrStop(float motorSpeed){
		if(ElevatorSafeToMove(motorSpeed)){
			MoveElevator(motorSpeed);
		} else{
			StopElevator();
		}
	}

	void MoveElevatorForTimeSafe(float motorSpeed, float time){
		float timeWaited = 0;

		while(timeWaited <= time){
			MoveElevatorSafeOrStop(motorSpeed);

			Wait(0.01);
			timeWaited += 10;
		}
	}

	void MoveElevatorMaxUp(float motorSpeed){
		MoveElevatorSafeOrStop(abs(motorSpeed));

		while(!mUpperElevatorLimitSwitch.Get()){}

		StopElevator();
	}

	void MoveElevatorMaxDown(float motorSpeed){
		MoveElevatorSafeOrStop(-1 * abs(motorSpeed));

		while(!mLowerElevatorLimitSwitch.Get()){}

		StopElevator();
	}

	void StopElevator(){
		mElevatorLeftMotor.StopMotor();
		mElevatorRightMotor.StopMotor();
	}

	//Robot
	void MoveRobot(float speed, float angle){
		mMyRobot.MecanumDrive_Polar(speed, angle, 0);
	}

	void StopRobot(){
		MoveRobot(0, 0);
	}

	void MoveRobotForTime(float speed, float angle, float time){
		float totalTime = 0;

		while(totalTime <= time){
			MoveRobot(speed, angle);

			Wait(10);
			totalTime += 10;
		}

		StopRobot();
	}

	void Autonomous(){
		/*
		 * Auto Plan:
		 * 		Bring claw up
		 * 			- Picks up barrel
		 * 		Drive forward
		 * 		Bring claw down
		 * 			- Releases barrel on box
		 * 		Bring claw up
		 * 			- Picks up box
		 * 		Turn 90 deg
		 * 		Go forward into auto zone
		 */

		//Bring Claw Up
		MoveElevator(kElevatorMotorSpeed);
		Wait(1);
		StopElevator();

		// -- We now have picked up a barrel

		//Drive Forward
		//MoveRobotForTime(0.2, 0, 2000);

		// -- The barrel is now above the crate

		//Bring Claw Down
		//MoveElevatorForTimeSafe(-1 * kElevatorMotorSpeed, 900);

		// -- We have now dropped the barrel on the crate

		//Drive Backward
		//MoveRobotForTime(-0.2, 0, 500);

		// -- We have now cleared the claw of the crate

		//Bring claw all the way down
		//MoveElevatorMaxDown(kElevatorMotorSpeed);

		// -- The claw is now in a position to pick up a crate

		//Move forward
		//MoveRobotForTime(0.2, 0, 600);

		// -- The robot and the claw are now in a position to pick up the crate

		//Bring claw up
		//MoveElevatorForTimeSafe(kElevatorMotorSpeed, 1200);

		// -- We now have a crate

		//Stafe to auto zone
		//MoveRobotForTime(0.5, 270, 1000);

		// -- We are now in the auto zone
	}

	void OperatorControl(){
		mDriverController.Calibrate();//Calibrate initially

		while (IsOperatorControl() && IsEnabled()){

			//Recalibrate if the Start button is pressed
			if(mDriverController.GetButton(mDriverController.BUTTON_START)){
				mDriverController.Calibrate();
			}

			if(mClawController.GetButton(mClawController.BUTTON_START)){
				mClawController.Calibrate();
			}

			//Vibrator Controller
			bool driverBackButton = mDriverController.GetButton(mDriverController.BUTTON_BACK);
			bool driverAButton = mDriverController.GetButton(mDriverController.BUTTON_A);

			bool clawBackButton = mClawController.GetButton(mClawController.BUTTON_BACK);
			bool clawAButton = mClawController.GetButton(mClawController.BUTTON_A);

			if(driverBackButton || clawAButton){
				mDriverController.RumbleLeft(1);
				mDriverController.RumbleRight(1);
			} else {
				mDriverController.RumbleLeft(0);
				mDriverController.RumbleRight(0);
			}

			if(clawBackButton || driverAButton){
				mClawController.RumbleLeft(1);
				mClawController.RumbleRight(1);
			} else {
				mClawController.RumbleLeft(0);
				mClawController.RumbleRight(0);
			}

			//Elevator control
			bool clawDPadUp = mClawController.GetDPad(mClawController.DPAD_UP);
			bool clawDPadDown = mClawController.GetDPad(mClawController.DPAD_DOWN);

			if(clawDPadUp){
				MoveElevatorSafeOrStop(kElevatorMotorSpeed);
			} else if(clawDPadDown){
				MoveElevatorSafeOrStop(-1 * kElevatorMotorSpeed);
			} else{
				StopElevator();
			}

			/*if(clawDPadUp && !mUpperElevatorLimitSwitch.Get()){
				mElevatorLeftMotor.Set(-1 *kElevatorMotorSpeed);
				mElevatorRightMotor.Set(kElevatorMotorSpeed);
			} else if(clawDPadDown && !mLowerElevatorLimitSwitch.Get()){
				mElevatorLeftMotor.Set(kElevatorMotorSpeed);
				mElevatorRightMotor.Set(-1 * kElevatorMotorSpeed);
			} else{
				mElevatorLeftMotor.StopMotor();
				mElevatorRightMotor.StopMotor();
			}*/


			/////////////////////////////////////////////////////
			///     AT THIS TIME WE ARE NOT USING THE ARMS    ///
			/////////////////////////////////////////////////////
			//Arms control
			/*bool clawDPadLeft = mClawController.GetDPad(mClawController.DPAD_LEFT);
			bool clawDPadRight = mClawController.GetDPad(mClawController.DPAD_RIGHT);

			if(clawDPadLeft){
				mArmsLeftMotor.Set(-1 * kArmsMotorSpeed);
				mArmsRightMotor.Set(kArmsMotorSpeed);
			} else if(clawDPadRight){
				mArmsLeftMotor.Set(kArmsMotorSpeed);
				mArmsRightMotor.Set(-1 * kArmsMotorSpeed);
			} else{
				mArmsLeftMotor.StopMotor();
				mArmsRightMotor.StopMotor();
			}*/

			//Arms wheel control
			/*bool clawLeftBumper = mClawController.GetButton(mClawController.BUTTON_LEFT_BUMPER);
			bool clawRightBumper = mClawController.GetButton(mClawController.BUTTON_RIGHT_BUMPER);

			bool clawLeftTrigger = mClawController.GetButton(mClawController.BUTTON_LEFT_TRIGGER);
			bool clawRightTrigger = mClawController.GetButton(mClawController.BUTTON_RIGHT_TRIGGER);

			if(clawLeftBumper && !clawLeftTrigger){
				mArmsWheelLeftMotor.Set(kArmsWheelMotorSpeed);
			} else if(!clawLeftBumper && clawLeftTrigger){
				mArmsWheelLeftMotor.Set(-1 * kArmsWheelMotorSpeed);
			} else {
				mArmsWheelLeftMotor.Set(0);
			}

			if(clawRightBumper && !clawRightTrigger){
				mArmsWheelRightMotor.Set(kArmsWheelMotorSpeed);
			} else if(!clawRightBumper && clawRightTrigger){
				mArmsWheelRightMotor.Set(-1 * kArmsWheelMotorSpeed);
			} else {
				mArmsWheelRightMotor.Set(0);
			}*/

			//Drive robot
			PolarCoord driverLeftStick = mDriverController.GetLeftStickPolar();

			float driveMagnitude = pow(driverLeftStick.magnitude, 2.0);
			float driveAngle = driverLeftStick.angle.angle;
			float driveRotation = pow(mDriverController.GetRightStickVector().x / 2, 2);

			bool driverRightBumper = mDriverController.GetButton(mDriverController.BUTTON_RIGHT_BUMPER);
			bool driverLeftBumper = mDriverController.GetButton(mDriverController.BUTTON_LEFT_BUMPER);

			if(driverRightBumper){
				float driveLockModeDifs[5];

				int i = 0;
				for(float lockModeValue : kDriveLockModeValues){
					driveLockModeDifs[i] = abs(driverLeftStick.angle.angle - lockModeValue);

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

				driveAngle = kDriveLockModeValues[lowestDifIndex];
			}

			if(mDriverController.GetRightStickVector().x < 0){
				driveRotation *= -1;
			}

			if(driverLeftBumper){
				printf("Dampeing");
				driveMagnitude = driveMagnitude / 2;
			}

			mMyRobot.MecanumDrive_Polar(driveMagnitude, driveAngle, driveRotation);
			//                              magnitude,  direction,      rotation

			Wait(0.005);//wait for a motor update time
		}
	}

	void Disabled(){}

};

START_ROBOT_CLASS(Robot);
