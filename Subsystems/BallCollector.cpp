#include "../Spike.h"
#include "../RobotMap.h"
#include "BallCollector.h"
#include "../Utils/Optical.h"


BallCollector::BallCollector() {
	topmotor = new Victor(TOP_CONVEYOR_MOTOR);
	bottommotor = new Victor(BOTTOM_CONVEYOR_MOTOR);
	
	//Motor Safety 
	topmotor->SetSafetyEnabled(true);
	topmotor->SetExpiration(0.5);
	bottommotor->SetSafetyEnabled(true);
	bottommotor->SetExpiration(0.5);
	
	topsensor = new LimitSensor(TOP_SENSOR, 1);
	bottomsensor = new LimitSensor(BOTTOM_SENSOR, 1);
	shootersensor = new LimitSensor(SHOOTER_SENSOR, 1);
	
	shooterState = SHOOTER_EMPTY_STATE;
	topState = TOP_CONVEYOR_EMPTY_STATE;
	bottomState = BOTTOM_CONVEYOR_EMPTY_STATE;
	

	ballcount = 0; 
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
			//if there is a ball in the shooter, the state is changed to full
			if (shootersensor->AtLimit() == 1) {
				shooterState = SHOOTER_FULL_STATE;
			}
		break;

		case SHOOTER_FULL_STATE:
			//if the ball is shot (not in the shooter anymore) then the ballcount
			//decreases by one and goes to empty state
			if (shootersensor->AtLimit() == 0) {
				ballcount--;
				shooterState = SHOOTER_EMPTY_STATE;
			}
		break;
		
		//default:
			//BothMotorsStop()	
	}
	
	//Top conveyor state machine

	switch(topState) {
		case TOP_CONVEYOR_EMPTY_STATE:
			//if the top conveyor sees a ball then the state is changed to full
			if (topsensor->AtLimit() == 1) {
				topState = TOP_CONVEYOR_FULL_STATE;
			}

			else TopConveyorMotorStart();
		break;

		case TOP_CONVEYOR_FULL_STATE:
			//if the shooter and top conveyor has a ball (is full) then 
			//the top conveyor motor stops. Otherwise, the conveyor motor 
			//cotinues to run.
			if (shooterState == SHOOTER_FULL_STATE) {
				TopConveyorMotorStop();
			}
			else TopConveyorMotorStart();
			
			if (topsensor->AtLimit() == 0) {
				TopConveyorMotorStart();
				topState = TOP_CONVEYOR_EMPTY_STATE;
			}
		break;

		//default:
			//TopConveyorMotorStart();
	}
	//Bottom conveyor state machine

	switch(bottomState) {
		case BOTTOM_CONVEYOR_FULL_STATE:
			if(bottomsensor->AtLimit() == 0) {
				ballcount++;
			}
			
			if (topState == TOP_CONVEYOR_FULL_STATE) {
				//if the ballcount is less than max (ball not in shooter but 
				//in top conveyor) then the bottom motor runs
				if (ballcount < MAX_BALLS) {
					BottomConveyorMotorStart();
				}
				//Otherwise, the motor is stopped
				else {
					BottomConveyorMotorStop();
				}
			}
			
			//Otherwise, start the bottom motor AND the upper conveyor motor
			else {
				BottomConveyorMotorStart();
				bottomState = BOTTOM_CONVEYOR_EMPTY_STATE;
			
				}
		break;

		case BOTTOM_CONVEYOR_EMPTY_STATE:
			//if the top conveyor motor is full and the ball count is less then 
			//max, run the bottom motor
			//Otherwise, stop the bottom motor
			if (topState == TOP_CONVEYOR_FULL_STATE) {
				if (ballcount < MAX_BALLS){
					BottomConveyorMotorStart();
				}
				else BottomConveyorMotorStop();
			}
			
			//Otherwise (if the top conveyor is not full) run the motor
			else BottomConveyorMotorStart();
			
			//If the bottom conveyor sees a ball, change state to full
			if (bottomsensor->AtLimit() == 1) {
				bottomState = BOTTOM_CONVEYOR_FULL_STATE;
			}
		break;
		
		//default:
			//BottomConveyorMotorStart();
			//TopConveyorMotorStart();
	}
}
