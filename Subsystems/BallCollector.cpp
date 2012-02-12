#include "../Spike.h"
#include "../RobotMap.h"
#include "BallCollector.h"

BallCollector::BallCollector() {
	topmotor = new Jaguar(TOP_CONVEYOR_MOTOR);
	bottommotor = new Jaguar(BOTTOM_CONVEYOR_MOTOR);
	
	//Motor Safety 
	topmotor->SetSafetyEnabled(true);
	topmotor->SetExpiration(0.5);
	bottommotor->SetSafetyEnabled(true);
	bottommotor->SetExpiration(0.5);
	
	topsensor = new DigitalInput(TOP_SENSOR);
	bottomsensor = new DigitalInput(BOTTOM_SENSOR);
	shootersensor = new DigitalInput(SHOOTER_SENSOR);

	ballcount = 0; 

	shooterState = SHOOTER_EMPTY_STATE;
	topState = TOP_CONVEYOR_EMPTY_STATE;
	bottomState = BOTTOM_CONVEYOR_EMPTY_STATE;
}

void BallCollector::BothMotorsStop() {
	topmotor->Set(0.0);
	bottommotor->Set(0.0);
}
void BallCollector::TopConveyorMotorStart() {
	topmotor->Set(0.5);
}

void BallCollector::TopConveyorMotorStop() {
	topmotor->Set(0.0);
}

void BallCollector::BottomConveyorMotorStart() {
	bottommotor->Set(0.5);
}

void BallCollector::BottomConveyorMotorStop() {
	bottommotor->Set(0.0);
}

void BallCollector::ConveyorStateMachine() {
	//Shooter state machine

	switch(shooterState) 
	{
		case SHOOTER_EMPTY_STATE:
			if (shootersensor->Get() == 1) {
				shooterState = SHOOTER_FULL_STATE;
			}
		break;

		case SHOOTER_FULL_STATE:
			if (shootersensor->Get() == 0) {
				ballcount--;
				shooterState = SHOOTER_EMPTY_STATE;
			}
		default:
			BothMotorsStop();
			cout << "ERROR!!! EXTERMINATE! EXTERMINATE!"; 
		break;
	}
	//Top conveyor state machine

	switch(topState) {
		case TOP_CONVEYOR_EMPTY_STATE:
			if (topsensor->Get() == 1) {
				topState = TOP_CONVEYOR_FULL_STATE;
			}
		break;

		case TOP_CONVEYOR_FULL_STATE:
			if (shooterState == SHOOTER_FULL_STATE) {
				TopConveyorMotorStop();
			}
			else {
				TopConveyorMotorStart();
			}
		break;

		default:
			BothMotorsStop();
			cout << "ERROR!!! EXTERMINATE! EXTERMINATE!";
		break;
	}
	//Bottom conveyor state machine

	switch(bottomState) {
		case BOTTOM_CONVEYOR_FULL_STATE:
			ballcount++;
			if (topState == 1) {
				if (ballcount < MAX_BALLS) {
					BottomConveyorMotorStart();
				}
				else {
					BottomConveyorMotorStop();
				}
			}
			else {
				bottomState = BOTTOM_CONVEYOR_EMPTY_STATE;
				BottomConveyorMotorStart();
			}

		case BOTTOM_CONVEYOR_EMPTY_STATE:
			if (topState == 1) {
				if (ballcount < MAX_BALLS) {
					BottomConveyorMotorStart();
					}
				else {
					BottomConveyorMotorStop();
				}
			if (bottomsensor->Get() == 1) {
				bottomState = BOTTOM_CONVEYOR_FULL_STATE;
			}

			}
		default:
			BothMotorsStop();
			cout << "ERROR!!!";
		break;
	}
}
