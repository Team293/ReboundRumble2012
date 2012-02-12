/*
 *	Name:
 *		Optical Sensor Class
 *
 *	Description:
 *		Uses WPILib DigitalInput class to acquire optical sensor input but provides
 *		option to reverse logic level sensing to keep isPresent() accessor method
 *		behavior consistent (i.e., TRUE => object is present in sensor).
 */
 
public class OpticalSensor
{
	private DigitalInput optical_sensor;
	private boolean reverse_sense;
	private boolean sensor_state;

	/*
	 *	Name: OpticalSensor
	 *
	 *	Description:
	 *		Class Constructor
	 *
	 *	Input:
	 *		optical_sensor_din_chnl	- Digital Input Channel for optical sensor
	 *		reserse_sense			- Option to reverse logic level sensing to alter normally
	 *								  high (1) input state
	 *
	 *	Return:
	 *		Object instance reference
	 */

	public OpticalSensor(int optical_sensor_din_chnl, boolean reverse_sense)
	{
		this.reverse_sense = reverse_sense;
		optical_sensor = new DigitalInput(optical_sensor_din_chnl);
	}


	/*
	 *	Name: isPresent
	 *
	 *	Description:
	 *		Accessor method that indicates optical sensor status
	 *
	 *	Input:
	 *		None
	 *
	 *	Return:
	 *		true	- object is present in sensor view
	 *		false	- no object present in sensor view
	 */

	public boolean isPresent()
	{
		sensor_state = optical_sensor.get();

		if (reverse_sense == true)
		{
			sensor_state = !sensor_state;
		}
		return(sensor_state);
	}
}