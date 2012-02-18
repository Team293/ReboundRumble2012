#ifndef COLLAR_H
#define COLLAR_H

#include "PIDController.h"
#include "PIDOutput.h"
#include "WPILib.h"
#include "../Utils/LimitSensor.h"


/*
 *	Name:
 *		Collar Class
 *
 *	Description:
 *		A template for an encoder-based distance PID subsystem. The PID control
 *		loop runs asynchronously in the background to achieve the desired
 *		setpoint. The base class setSetpoint() method changes the setpoint the
 *		PID controller is trying to reach. The PID Input is an encoder hooked
 *		up to the mechanical components and the PID Output drives the mechanism
 *		motor according to the calculated PID control value.
 *
 */
 

class Collar : public PIDOutput {

private:
	// Declare PID coefficients
	// Tune for actual mechanism
	static const double Kp = 0.1;
	static const double Ki = 0.0;
	static const double Kd = 0.0;

	// Subsystem Member Variables
	double	m_position_setpoint;

	// Declare Subsystem PWM, limit sensors, position encoder references, and PID Controller
	Jaguar			*collar_motor_pwm;
	LimitSensor		*collar_fwd_lim_sensor;
	LimitSensor		*collar_rev_lim_sensor;
	Encoder			*collar_encoder;
	PIDController	*collar_PIDController;

	//Collar constants
	static const double COLLAR_DIST_PER_REV = 1.0/10.0;
	static const double COLLAR_ENCDR_REV_PER_COUNT = 1.0/(128.0);

	static const double COLLAR_SETPOINT_TOLERANCE = 0.01;

	static const double COLLAR_HOMING_SEQ_FWD_SPEED = 0.5;
	static const double COLLAR_HOMING_SEQ_REV_SPEED = -0.1;


public:
    // Constants for preset positions of the Subsystem
    // Modify and add positions as appropriate for actual mechanism
	static const double COLLAR_HOME_POS = 0.0;
	static const double COLLAR_START_POS = 1.00;

	// Declare Subsystem Methods
	Collar();
	void CollarInit();
	void SetPosition(float position_setpoint);
	double GetPosition();
	bool AtPosition();
	void PIDWrite(float pid_output);
	bool AtCollarFwdLimit();
	bool AtCollarRevLimit();
};

#endif

