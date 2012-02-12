#include "Spike.h"


Spike::Spike(void) { 
	//Include all definitions of Subsystems, global variables, and
	//OI interface here
	
	//Subsystems
	ballcollector = new BallCollector();
	collar = new Collar();
	drivetrain = new Drivetrain();
	passer = new Passer();
	puncher = new Puncher();
	turret = new Turret();
	vision = new Vision();
	
	//Global Variables
	
	//OI interface
}
	
Spike::~Spike() {	
	delete ballcollector;
	delete collar;
	delete drivetrain;
	delete passer;
	delete puncher;
	delete turret;
	delete vision;
}

void Spike::RobotInit(void) {

}
	
//Autonmous
void Spike::AutonomousInit(void) {

}

void Spike::AutonomousPeriodic(void) {
	
}

void Spike::AutonomousContinuous(void) {
	
}

//Teleop
void Spike::TeleopInit(void) {
	
}

void Spike::TeleopPeriodic(void) {
	
}

void Spike::TeleopContinuous(void) {
	
}

//Disabled
void Spike::DisabledInit(void) {	

}

void Spike::DisabledPeriodic(void){

}

void Spike::DisabledContinuous(void){

}

START_ROBOT_CLASS(Spike);
