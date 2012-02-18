#ifndef PUNCHER_H
#define PUNCHER_H
#include "WPILib.h"
#include "../Utils/LimitSensor.h"

class Puncher {
private:
	Jaguar * punchermotor;
	
	LimitSensor * punchersensor;
	
	int	PuncherState;
	
	//Puncher Constants
	static const int PUNCHER_STOP_STATE = 0;
	static const int PUNCHER_START_STATE = 1;
	static const int PUNCHER_RUN_STATE = 2;
public:
	Puncher();
	void PuncherMotorStart();
	void PuncherMotorStop();
	void PuncherRun(bool start_puncher);

};

#endif
 
