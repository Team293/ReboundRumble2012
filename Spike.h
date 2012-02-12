#ifndef SPIKE_H
#define SPIKE_H

#include "WPILib.h"
#include "RobotMap.h"

#include "Subsystems/BallCollector.h"
#include "Subsystems/Collar.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Passer.h"
#include "Subsystems/Puncher.h"
#include "Subsystems/Turret.h"
#include "Subsystems/Vision.h"

class Spike : public IterativeRobot {
	//Include all creations of subsystems, global variables, and
	//OI interface here
	
	//Subsystems
	BallCollector * ballcollector ;
	Collar * collar;
	Drivetrain * drivetrain;
	Passer * passer;
	Puncher * puncher;
	Turret * turret;
	Vision * vision;

	//OI
	
	//Global Variables
	
public:
	Spike();
	~Spike();	
	void RobotInit();
	
	void AutonomousInit();//auto code in Autonomous.cpp
	void AutonomousContinuous();
	void AutonomousPeriodic();
	
	void TeleopInit();//teleop code in Teleop.cpp
	void TeleopContinuous();
	void TeleopPeriodic();
	
	void DisabledInit();
	void DisabledContinuous();
	void DisabledPeriodic();
};

#endif
