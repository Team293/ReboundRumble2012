#include "../Spike.h"
#include "../RobotMap.h"
#include "Collar.h"
#include "Math.h"
#include "../Utils/LimitSensor.h"

/**
 *	Name:
 *		EncoderSubsystem
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

Collar::Collar() {

	// Create Subsystem motor PWM reference
	// and disable SafePWM operation
	collar_motor_pwm = new Jaguar(COLLAR_MOTOR_PWM);

	// Create Subsystem limit sensor references; set reverse logic sensing
	collar_fwd_lim_sensor = new LimitSensor(COLLAR_FWD_LIM_DIN, true);
	collar_rev_lim_sensor = new LimitSensor(COLLAR_REV_LIM_DIN, true);

	// Create Subsystem encoder reference and configure to provide distance measurements
	collar_encoder = new Encoder(COLLAR_ENCDR_ACHNL_DIN, COLLAR_ENCDR_BCHNL_DIN, false, Encoder::k4X);
	collar_encoder->SetDistancePerPulse(COLLAR_DIST_PER_REV * COLLAR_ENCDR_REV_PER_COUNT);
	collar_encoder->SetPIDSourceParameter(Encoder::kDistance);

	// Create Subsystem PID Controller and supply
	//	PID coefficients
	//	Encoder reference as PID Source
	//	Encoder Subsystem reference (this) as PID Output that will implement PIDWrite interface method
	collar_PIDController = new PIDController(Kp, Ki, Kd, collar_encoder, this, 0.020);
	//NEED TO CHANGE LATER!!!
	collar_PIDController->SetInputRange(0.0, 6.0);
}


/**
 *	Name:
 *		InitEncoderSubsystem
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

void Collar::CollarInit() {
	// Home Subsystem to initialize position encoder

	// If already on reverse limit, move forward off home position
	// to provide a repeatable homing sequence.

	if (collar_rev_lim_sensor->AtLimit() == true)
	{
		// Move forward off home position until clear of limit
		while (collar_rev_lim_sensor->AtLimit() == true)
		{
			collar_motor_pwm->Set(COLLAR_HOMING_SEQ_FWD_SPEED);
		}
		collar_motor_pwm->Set(0.0);
	}

	// Start homing sequence by moving toward reverse limit
	// position and stop when reverse limit reached.
	while (collar_rev_lim_sensor->AtLimit() == false)
	{
		collar_motor_pwm->Set(COLLAR_HOMING_SEQ_REV_SPEED);
	}
	collar_motor_pwm->Set(0.0);
	collar_encoder->Reset();
	collar_encoder->Start();

	// Enable the PID Controller to start PID running in the background
	// and set the starting setpoint  
	collar_PIDController->Enable();
	collar_PIDController->SetSetpoint(COLLAR_START_POS);
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

void Collar::SetPosition(float position_setpoint) {
	m_position_setpoint = position_setpoint;
	collar_PIDController->SetSetpoint(position_setpoint);
}


/**
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

double Collar::GetPosition() {
	return(collar_encoder->GetDistance() );
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

bool Collar::AtPosition() {
	return ( fabs(collar_encoder->GetDistance() - m_position_setpoint) < COLLAR_SETPOINT_TOLERANCE );
}


/**
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

void Collar::PIDWrite(float pid_output) {
	float pwm_output;

	pwm_output = pid_output;

	// Check if reverse limit sensor is active when traveling
	// in the reverse direction and stop movement
	if ( (pid_output < 0.0) && (collar_rev_lim_sensor->AtLimit() == true) )
	{
		pwm_output = 0.0;
	}

	// Check if forward limit sensor is active when traveling
	// in the forward direction and stop movement
	if ( (pid_output > 0.0) && (collar_fwd_lim_sensor->AtLimit() == true) )
	{
		pwm_output = 0.0;
	}

	// Drive the Subsystem motor according to qualified PID output
	collar_motor_pwm->Set(pwm_output);
}

bool Collar::AtCollarFwdLimit() {
	if (collar_fwd_lim_sensor->AtLimit() ==true) {
			return true;
		}
	else return false;
}

bool Collar::AtCollarRevLimit() {
	if (collar_rev_lim_sensor->AtLimit() ==true) {
			return true;
		}
	else return false;
}
