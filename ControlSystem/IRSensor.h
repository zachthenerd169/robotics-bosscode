/*
 * IRSensor.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 *
 * Class description: IRSensor reads IRSensors and then stores that value
 */

#ifndef IRSENSOR_H_
#define IRSENSOR_H_


class IRSensor : Sensor
{
	public:
		/**
		 * Description: returns m_value which will be casted to a string
		 * Input: none
		 * Output: m_value
		 */
		std::string readCurrentValue();
		/**
	     * Description: gets the current value from the physical IR sensor and stores in
	     * 				m_value
		 * Input: none
		 * Output: returns true if sensor value was successfully read, false otherwise.
		 * 		  (it may be false if the sensor is broken, or the connection between the NUC
		 * 		  and sensor is broken)
		 */
		bool updateValue();
	private:
		/**
		 * value of the IRSensor
		 */
		double m_value;
};


#endif /* IRSENSOR_H_ */
