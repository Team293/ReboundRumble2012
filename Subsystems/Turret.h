#ifndef TURRET_H
#define TURRET_H

#include "WPILib.h"
#include "PIDController.h"
#include "PIDOutput.h"
#include "../Utils/LimitSensor.h"

/**
 *	Name:
 *		Encoder Subsystem Class
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

class Turret: public PIDOutput {
private:
	// Declare PID coefficients
		// Tune for actual mechanism
		static const double Kp = 0.1;
		static const double Ki = 0.0;
		static const double Kd = 0.0;
		
		//YEAH, WE DON'T NEED THIS CURRENTLY... 
	    // Constants for Subsystem mechanism and encoder NEED TO SET LATER!! 
		// Example Constants (change as appropriate):
		//	10 revs per 1 degree lead screw
		//	128 count per rev encoder @ 4x resolution UPDATE: don't need to add
		//  	resolution to make things work
		//static const double TURRET_ANGLE_PER_REV = 1.0/10.0;
		//static const double TURRET_ENCDR_REV_PER_COUNT = 1.0/(128.0);
		//static const double SUBSYS_DIST_PER_COUNT = SUBSYS_DIST_PER_REV * SUBSYS_ENCDR_REV_PER_COUNT;

		static const double TURRET_DEGREES_PER_COUNT = 360/128;
		
		// Tolerance for error between setpoint and current position
		// Example value; adjust to target mechanism tolerance
		static const double SETPOINT_TOLERANCE = 0.01;

		// Homing sequence constants
		// Example Constants (change as appropriate)
		static const double TURRET_HOMING_SEQ_FWD_SPEED = 0.3;
		static const double TURRET_HOMING_SEQ_REV_SPEED = -0.5;
		
		// Subsystem Member Variables
		float	m_position_setpoint;
		
		// Declare Subsystem PWM, limit sensors, position encoder references, and PID Controller
		Encoder			*turret_encoder;
		PIDController	*turret_PIDController;
		LimitSensor		*turret_fwd_lim_sensor;
		LimitSensor		*turret_rev_lim_sensor;
		Jaguar			*turret_motor_pwm;
	
public:
	 // Constants for preset positions of the Subsystem
	 // Modify and add positions as appropriate for actual mechanism
	static const double TURRET_START_POS = 0.0;

	 // Declare Subsystem Methods
	Turret();
    void InitEncoderTurret();
	void SetPosition(float position_setpoint);
	double GetPosition();
	bool AtPosition();
	void PIDWrite(float pid_output);
	void DriveMotor();
	bool AtTurretFwdLimit();
	bool AtTurretRevLimit();
};

#endif
