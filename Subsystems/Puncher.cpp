#include "../Spike.h"
#include "../RobotMap.h"
#include "Puncher.h"

Puncher::Puncher() {
	//punchermotor = new Jaguar(PUNCHER_MOTOR);
	//punchersensor = new DigitalInput(PUNCHER_SENSOR);
}

void Puncher::PuncherMotorStart() {
	//punchermotor->Set(1.0);
}

void Puncher::PuncherMotorStop() {
	//punchermotor->Set(0.0);
}

void Puncher::PuncherControl(){
	/*if (punchersensor->Get() == 1){
		PuncherMotorStart();
	}
*/
}

void Puncher::PuncherRun() {
	/*if (!(punchersensor->Get()==1)) {
		PuncherMotorStart();
	}	
	else PuncherMotorStop();
	*/
}
