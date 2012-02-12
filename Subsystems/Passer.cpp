#include "../Spike.h"
#include "../RobotMap.h"
#include "Passer.h"

// Does not work yet 
// 1/30/12 I.G.

Passer::Passer() {
	passermotor = new Jaguar(9);

	//Motor Safetys
	passermotor->SetSafetyEnabled(true);
	passermotor->SetExpiration(0.5);
}

void Passer::PasserMotorStart() {
	passermotor->Set(0.5);
}

void Passer::PasserMotorStop() {
	passermotor->Set(0.0);
}
