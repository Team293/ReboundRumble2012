#ifndef LIMIT_SENSOR_H
#define LIMIT_SENSOR_H

#include "WPILib.h"


/**
 *	Name:
 *		Limit Sensor Class
 *
 *	Description:
 *		Uses WPILib DigitalInput class to acquire optical sensor input but provides
 *		option to reverse logic level sensing to keep isPresent() accessor method
 *		behavior consistent (i.e., TRUE => object is present in sensor).
 */
  
class LimitSensor{
private:
	// Declare class variables
	bool reverse_sense;
	bool limit_state;

	// Declare limit sensor reference
	DigitalInput	*limit_sensor;

public:
	// Declare Subsystem Methods
	LimitSensor(UINT32 limit_sensor_din_chnl, bool reverse_sense);
	bool AtLimit();
};

#endif
