/*
 *	Name:
 *		Ball Puncher Subsystem Class
 *
 *	Description:
 *		Contains methods to control Ball Puncher subsystem
 */

public class PuncherSubsystem
{
	// Puncher State Machine States

	private static final int PUNCHER_STOP_STATE = 0;
	private static final int PUNCHER_START_STATE = 1;
	private static final int PUNCHER_RUN_STATE = 2;

	// Ball Puncher State Variables

	private static int	PuncherState;

	// Ball Sensor object references

	private OpticalSensor puncher_position_sensor;

	// Puncher Motor object reference

	//private Victor puncher_motor_pwm;


	/*
	 *	Name: BallPuncherSubsystem
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

	public PuncherSubsystem()
	{
		// Set State Machine to initial state

		PuncherState = PUNCHER_STOP_STATE;

		// Create instances of Puncher Subsystem Cam Position Sensor
		// Note: data_in parameter only used for testing not in actual LimitSensor class

		puncher_position_sensor = new OpticalSensor(RobotMap.PUNCHER_POSITION_SENSOR_DIN_CHNL, true);

		// Create instances of Collector Subsystem Motors

		//puncher_motor_pwm = new Victor(RobotMap.PUNCHER_MOTOR_PWM_CHNL);
	}


	/*
	 *	Name: runPuncher
	 *
	 *	Description:
	 *		Runs the Ball Puncher Subsystem state machine.
	 *
	 *		The state machine method is intendedd to be invoked periodically (e.g., every Iterative Robot
	 *		framework Periodic loop) to provide high enough sampling rate for proper sensor input and
	 *		actuator control.
	 *
	 *	Input:
	 *		None
	 *
	 *	Return:
	 *		None
	 */

	public void runPuncher(boolean start_puncher)
	{
		// Puncher State Machine

		switch (PuncherState)
		{
		    case PUNCHER_STOP_STATE:
		        if ( start_puncher == true )
		        {
		            // Puncher signaled to start
					runPuncherMotor();
					PuncherState = PUNCHER_START_STATE;
		        }
				else
				{
					// Otherwise keep the motor safety helper happy by
					// continuing to signal the puncher motor is stopped
					stopPuncherMotor();
				}
		    break;

		    case PUNCHER_START_STATE:
				// Continue to run the puncher motor
				runPuncherMotor();

				if ( puncher_position_sensor.isPresent() == false )
		        {
		            // If the puncher has cleared the position sensor
					// then go to the RUN state
					PuncherState = PUNCHER_RUN_STATE;
		        }
		    break;

		    case PUNCHER_RUN_STATE:
		        if ( puncher_position_sensor.isPresent() == true )
		        {
		            // If the puncher position sensor detects the
					// stopped position, then stop the puncher motor
					// and go to the STOP state
					stopPuncherMotor();
		            PuncherState = PUNCHER_STOP_STATE;
		        }
				else
				{
					// Otherwise keep the motor safety helper happy by
					// continuing to signal the puncher motor is running
					runPuncherMotor();
				}
		    break;

		    default:
		        // Handle illegal state here
		        System.out.println("ERROR: Puncher State Machine illegal state:" + PuncherState);
		    break;
		}
	}


	/*
	 *	Name: isReadyToShoot
	 *
	 *	Description:
	 *		Accessor method that indicates that the puncher is in position to shoot.
	 *
	 *	Input:
	 *		None
	 *
	 *	Return:
	 *		true	- Puncher in position to shoot
	 *		false	- Puncher is not in position to shoot
	 */

	public boolean isReadyToShoot()
	{
		return( puncher_position_sensor.isPresent() );
	}


	/*
	 *	Name: runPuncherMotor
	 *
	 *	Description:
	 *		Private Ball Puncher method that turns the Puncher Motor on.
	 *
	 *	Input:
	 *		None
	 *
	 *	Return:
	 *		None
	 */

	private void runPuncherMotor()
	{
		puncher_motor_pwm.set(1.0);
	}


	/*
	 *	Name: stopPuncherMotor
	 *
	 *	Description:
	 *		Private Ball Puncher method that turns the Puncher Motor off.
	 *
	 *	Input:
	 *		None
	 *
	 *	Return:
	 *		None
	 */

	private void stopPuncherMotor()
	{
		puncher_motor_pwm.set(0.0);
	}
}