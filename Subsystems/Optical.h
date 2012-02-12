#ifndef OPTICAL_H
#define OPTICAL_H
#include "WPILib.h"

class Optical {
private:
	DigitalInput *optical_sensor;
	
	bool reverse_sense;
	bool sensor_state;
	
public:
	Optical(int optical_sensor_din_chnl, bool reverse_sense);
	bool isPresent();
};

#endif
