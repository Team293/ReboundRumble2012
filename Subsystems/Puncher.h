#ifndef PUNCHER_H
#define PUNCHER_H
#include "WPILib.h"

class Puncher {
private:
	Jaguar *punchermotor;
	
	DigitalInput *punchersensor;
	
	int	PuncherState;
	
public:
	Puncher();
	void PuncherMotorStart();
	void PuncherMotorStop();
	void PuncherRun(bool start_puncher);

};

#endif
 
