#include "LimitSensor.h"
#include "../Robotmap.h"


/**
 *	Name:
 *		LimitSensor
 *
 *	Description:
 *		Class Constructor
 *
 *	Input:
 *		limit_sensor_din_chnl	The digital input channel on DIO module 1 (default)
 *								where the limit sensor is located.
 *		reverse_sense			The option to reservse the limit sense output state
 *								from the actual limit sensor state reported via
 *								digital input channel.
 *
 *	Return:
 *		Object instance reference
 */

LimitSensor::LimitSensor(UINT32 limit_sensor_din_chnl, bool reverse_sense) {
	// Create instance of specified limit sensor and store sense qualifier
	limit_sensor = new DigitalInput(limit_sensor_din_chnl);
	this->reverse_sense = reverse_sense;
}


/**
 *	Name:
 *		AtLimit
 *
 *	Description:
 *		Accessor method that indicates limit sensor status
 *
 *	Input:
 *		None
 *
 *	Return:
 *		true	If limit sensor active
 *		false	If limit sensor inactive
 */

bool LimitSensor::AtLimit()
{
	bool limit_state;

	limit_state = limit_sensor->Get();

	if (reverse_sense == true)
	{
		limit_state = !limit_state;
	}
	return(limit_state);
}
