/*
 * MecanumDrive.h
 *
 *  Created on: Jan 25, 2016
 *      Author: Benjamin
 */

#ifndef MECANUM_DRIVE_H
#define MECANUM_DRIVE_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class MecanumDrive: public Subsystem
{
private:
	RobotDrive rob;
public:
	MecanumDrive(RobotDrive robot);
	void InitDefaultCommand();
	void move(float speed, float direction);
};



#endif /* SRC_SUBSYSTEMS_MECANUMDRIVE_H_ */
