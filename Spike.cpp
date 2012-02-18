#include "Spike.h"
#include "math.h"

Spike::Spike(void) { 
	//Include all definitions of Subsystems, OI interface, and
	//global variables here
	
	//Subsystems
	ballcollector = new BallCollector();
	collar = new Collar();
	drivetrain = new Drivetrain();
	passer = new Passer();
	puncher = new Puncher();
	turret = new Turret();
	vision = new Vision();
	
	//OI interface
	lstick = new Joystick(LEFT_JOYSTICK_PORT);
	rstick = new Joystick(RIGHT_JOYSTICK_PORT);
	gamepad = new Joystick(GAMEPAD_PORT);
	
	puncherbutton = new JoystickButton(lstick, PUNCHER_BUTTON);
	//Global Variables
	turretinput = 0.0;
	collarinput = 0.0;
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
	//Collar
	collar->CollarInit();
	
	//Turret
	turret->InitEncoderTurret();
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
	//Drive Code
	//drivetrain->tankDrive(lstick->GetY(), rstick->GetY());
	
	//Collector
	//ballcollector->ConveyorStateMachine();
	
	//Ball Puncher
	//puncher->PuncherRun(puncherbutton->Get());
	
	//Collar
	collarinput = (5*(gamepad->GetRawAxis(2))) + collarinput;
		if (collar->AtCollarFwdLimit() == true) {
			collarinput = 5.0;
		}

		if (collar->AtCollarRevLimit() == true) {
			collarinput = 0.0;
		}
		
		collar->SetPosition(collarinput);
	
	//Turret
	turretinput = (5*(gamepad->GetRawAxis(1))) + turretinput;
	if (turret->AtTurretFwdLimit() == true) {
		turretinput = 60.0;
	}

	if (turret->AtTurretRevLimit() == true) {
		turretinput = 0.0;
	}
	
	turret->SetPosition(turretinput);
	
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
