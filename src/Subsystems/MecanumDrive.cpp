/*
 * MecanumDrive.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: Benjamin
 */
#include "ExampleSubsystem.h"
#include "../RobotMap.h"

MecanumDrive::MecanumDrive(RobotDrive robot) :Subsystem("MecanumDrive"){
	rob=robot;
}

void MecanumDrive::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void MecanumDrive::move(float speed, float direction){
	rob.MecanumDrive_Polar(speed, direction, 0);
}




