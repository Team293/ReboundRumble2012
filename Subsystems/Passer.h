#ifndef PASSER_H
#define PASSER_H
#include "WPILib.h"

class Passer {
public:
	Passer();
	void PasserMotorStart();
	void PasserMotorStop();

private:
	Jaguar *passermotor;
};

#endif
