#include "../Spike.h"
#include "../RobotMap.h"
#include "Drivetrain.h"

Drivetrain::Drivetrain() {
	drive = new RobotDrive(LEFT_DRIVE,RIGHT_DRIVE); //2 for left port, 3 for right

	drive->SetSafetyEnabled(true);
	drive->SetExpiration(0.5);
}

void Drivetrain::tankDrive(double left, double right){
	drive->TankDrive(left, right);
}

