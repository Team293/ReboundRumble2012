#include "../Spike.h"
#include "../RobotMap.h"
#include "Puncher.h"
#include "../Utils/LimitSensor.h"


Puncher::Puncher() {
	punchermotor = new Jaguar(PUNCHER_MOTOR);
	punchersensor = new LimitSensor(PUNCHER_SENSOR, 1);
	
	PuncherState = PUNCHER_STOP_STATE;
}

void Puncher::PuncherMotorStart() {
	punchermotor->Set(0.5);
}

void Puncher::PuncherMotorStop() {
	punchermotor->Set(0.0);
}

void Puncher::PuncherRun(bool start_puncher) {
	switch (PuncherState)
			{
			    case PUNCHER_STOP_STATE:
			        if ( start_puncher == 1 )
			        {
			            // Puncher signaled to start
						PuncherMotorStart();
						PuncherState = PUNCHER_START_STATE;
			        }
					else
					{
						// Otherwise keep the motor safety helper happy by
						// continuing to signal the puncher motor is stopped
						PuncherMotorStop();
					}
			    break;

			    case PUNCHER_START_STATE:
					// Continue to run the puncher motor
					PuncherMotorStart();

					if ( punchersensor->AtLimit() == 0)
			        {
			            // If the puncher has cleared the position sensor
						// then go to the RUN state
						PuncherState = PUNCHER_RUN_STATE;
			        }
			    break;

			    case PUNCHER_RUN_STATE:
			        if ( punchersensor->AtLimit() == 1)
			        {
			            // If the puncher position sensor detects the
						// stopped position, then stop the puncher motor
						// and go to the STOP state
						PuncherMotorStop();
			            PuncherState = PUNCHER_STOP_STATE;
			        }
					else
					{
						// Otherwise keep the motor safety helper happy by
						// continuing to signal the puncher motor is running
						PuncherMotorStart();
					}
			    break;

			    default:
			        // Handle illegal state here
			       
			    break;
			}
		}
