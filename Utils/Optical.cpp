#include "../Spike.h"
#include "../Robotmap.h"
#include "Optical.h"

Optical::Optical(int optical_sensor_din_chnl, bool reverse_sense) {
	this->reverse_sense = reverse_sense;
	optical_sensor = new DigitalInput(optical_sensor_din_chnl); 
}

bool Optical::Get() {
	sensor_state = optical_sensor->Get();
	if (reverse_sense == 1)
			{
				sensor_state = !sensor_state;
			}
		return(sensor_state);
}
