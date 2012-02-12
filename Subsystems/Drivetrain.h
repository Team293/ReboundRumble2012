#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "WPILib.h"


class Drivetrain {
private:
	RobotDrive *drive;
public:
	Drivetrain();
	void tankDrive(double left, double right);
};

#endif
