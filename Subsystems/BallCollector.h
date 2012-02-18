#ifndef BALLCOLLECTOR_H
#define BALLCOLLECTOR_H
#include "WPILib.h"
#include "../Utils/LimitSensor.h"

class BallCollector {
public:
	BallCollector();
	void BothMotorsStop();
	void TopConveyorMotorStart();
	void TopConveyorMotorStop();
	void BottomConveyorMotorStart();
	void BottomConveyorMotorStop();
	void ConveyorStateMachine();

private:
	Victor *topmotor;
	Victor *bottommotor;
	
	LimitSensor *bottomsensor;
	LimitSensor *topsensor;
	LimitSensor *shootersensor;

	int ballcount;

	bool shooterState;
	bool topState;
	bool bottomState;
	
	//Conveyor constants
	static const int MAX_BALLS = 3;

	static const int BOTTOM_CONVEYOR_EMPTY_STATE = 0;
	static const int BOTTOM_CONVEYOR_FULL_STATE = 1;

	static const int TOP_CONVEYOR_EMPTY_STATE = 0;
	static const int TOP_CONVEYOR_FULL_STATE = 1;

	static const int SHOOTER_EMPTY_STATE = 0;
	static const int SHOOTER_FULL_STATE = 1;
};

#endif
