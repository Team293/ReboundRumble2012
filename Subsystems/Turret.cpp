#include "../Spike.h"
#include "../Robotmap.h"
#include "Turret.h"
#include "../Utils/LimitSensor.h"
#include "math.h"


/**
 *	Name:
 *		Turret
 *
 *	Description:
 *		Class Constructor
 *
 *	Input:
 *		None
 *
 *	Return:
 *		Object instance reference
 */

Turret::Turret() {
	// Create Subsystem motor PWM reference
	// and set safeties
	turret_motor_pwm = new Jaguar(TURRET_MOTOR_PWM);
	
	turret_motor_pwm->SetSafetyEnabled(true);
	turret_motor_pwm->SetExpiration(0.5);
	
	// Create Subsystem limit sensor references; set reverse logic sensing
	turret_fwd_lim_sensor = new LimitSensor(TURRET_FWD_LIM_DIN, 1);
	turret_rev_lim_sensor = new LimitSensor(TURRET_REV_LIM_DIN, 1);

	// Create Subsystem encoder reference and configure to provide distance measurements
	turret_encoder = new Encoder(TURRET_ENCDR_ACHNL_DIN, TURRET_ENCDR_BCHNL_DIN, false, Encoder::k4X);
	turret_encoder->SetDistancePerPulse(TURRET_DEGREES_PER_COUNT);
	turret_encoder->SetPIDSourceParameter(Encoder::kDistance);

	// Create Subsystem PID Controller and supply
	//	PID coefficients
	//	Encoder reference as PID Source
	//	Encoder Subsystem reference (this) as PID Output that will implement PIDWrite interface method
	turret_PIDController = new PIDController(Kp, Ki, Kd, turret_encoder, this, 0.020);
	turret_PIDController->SetInputRange(0.0, 60.0);
}


/**
 *	Name:
 *		InitEncoderTurret
 *
 *	Description:
 *		Initialize encoder used in PID subsystem.
 *
 *	Input:
 *		None
 *
 *	Return:
 *		None
 */

void Turret::InitEncoderTurret() {
	// Home Subsystem to initialize position encoder

	// If already on reverse limit, move forward off home position
	// to provide a repeatable homing sequence.
	
	if (turret_rev_lim_sensor->AtLimit())
	{
		// Move forward off home position until clear of limit
		while (turret_rev_lim_sensor->AtLimit())
		{
			turret_motor_pwm->Set(TURRET_HOMING_SEQ_FWD_SPEED);
		}
		turret_motor_pwm->Set(0.0);
	}

	// Start homing sequence by moving toward reverse limit
	// position and stop when reverse limit reached.
	while (turret_rev_lim_sensor->AtLimit() == false)
	{
		turret_motor_pwm->Set(TURRET_HOMING_SEQ_REV_SPEED);
	}
	turret_motor_pwm->Set(0.0);
	turret_encoder->SetReverseDirection(true);
	turret_encoder->Reset();
	turret_encoder->Start();
	
	// Enable the PID Controller to start PID running in the background
	// and set the starting setpoint  
	turret_PIDController->Enable();
	turret_PIDController->SetSetpoint(TURRET_START_POS);
}


/**
 *	Name:
 *		SetPosition
 *
 *	Description:
 *		Sets the subsystem position PID setpoint.
 *
 *	Input:
 *		position	The position value to set the PID setpoint.
 *
 *	Return:
 *		None
 */


void Turret::SetPosition(float position_setpoint) {
	m_position_setpoint = position_setpoint;
	turret_PIDController->SetSetpoint(position_setpoint);	
}


/*
 *	Name:
 *		GetPosition
 *
 *	Description:
 *		Sets the subsystem position PID setpoint.
 *
 *	Input:
 *		None
 *
 *	Return:
 *		position	The subsystem current position.
*/


double Turret::GetPosition() {
	return( turret_encoder->GetDistance() );
}


/**
 *	Name:
 *		AtPosition
 *
 *	Description:
 *		Indicates if the current position is at the desired setpoint within
 *		an acceptable error tolerance for the subsystem mechanism.
 *
 *	Input:
 *		None
 *
 *	Return:
 *		true	Current position is within acceptable tolerance of setpoint.
 *		false	Current position is not within acceptable tolerance of setpoint.
*/
 

bool Turret::AtPosition() {
	return( fabs(turret_encoder->GetDistance() - m_position_setpoint) < SETPOINT_TOLERANCE );
}

/*
 *	Name:
 *		PIDwrite
 *
 *	Description:
 *		Implements PIDOutput interface method to drives subsystem motor based
 *		on current PID output calculation and guarded by limit sensors.
 *
 *	Input:
 *		pid_output	The value to set via the PID algorithm call to subsystem
 *					PIDWrite() method. This gets called each time through
 *					the PID loop to update the output to the motor.
 *
 *	Return:
 *		None
 */

void Turret::PIDWrite(float pid_output) {
	float pwm_output;

	pwm_output = pid_output;

	// Check if reverse limit sensor is active when traveling
	// in the reverse direction and stop movement
	if ( (pid_output < 0.0) && (turret_rev_lim_sensor->AtLimit() == true) )
	{
		pwm_output = 0.0;
	}

	// Check if forward limit sensor is active when traveling
	// in the forward direction and stop movement
	if ( (pid_output > 0.0) && (turret_fwd_lim_sensor->AtLimit() == true) )
	{
		pwm_output = 0.0;
	}

	// Drive the Subsystem motor according to qualified PID output
	turret_motor_pwm->Set(pwm_output);
	
}

bool Turret::AtTurretFwdLimit() {
	if (turret_fwd_lim_sensor->AtLimit() == true) {
		return true;
	}
	
	else return false;
}

bool Turret::AtTurretRevLimit() {
	if (turret_rev_lim_sensor->AtLimit() ==true) {
		return true;
	}
	
	else return false;
}
