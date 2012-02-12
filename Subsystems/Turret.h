#ifndef TURRET_H
#define TURRET_H

#include "WPILib.h"

class Turret: public PIDSubsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	// set the P, I, and D constants here
	static const double Kp = 0.0;
	static const double Ki = 0.0;
	static const double Kd = 0.0;
	
	Encoder *turretencoder;
public:
	Turret();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
};

#endif
