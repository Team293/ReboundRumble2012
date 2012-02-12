#ifndef PUNCHER_H
#define PUNCHER_H
#include "WPILib.h"

class Puncher {
private:
	Jaguar *punchermotor;
	
	DigitalInput *punchersensor;
	
public:
	Puncher();
	void PuncherMotorStart();
	void PuncherMotorStop();
	void PuncherControl();
	void PuncherRun();

};

#endif
 
