/*
 * LaserRangeFinder.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 *
 * Class Description: LaserRangeFinder reads laser range finders and then stores that value
 */

#ifndef LASERRANGEFINDER_H_
#define LASERRANGEFINDER_H_

class LaserRangeFinder : public Sensor
{
	public:
		/**
		 * Description: returns m_value which will be casted to a string
		 * Input: none
		 * Output: m_value
		 */
		std::string readCurrentValue();
		/**
		 * Description: gets the current value from the physical long range finder and stores in
	     * 				m_value
		 * Input: none
		 * Output: returns true if sensor value was successfully read, false otherwise.
		 * 		  (it may be false if the sensor is broken, or the connection between the NUC
		 * 		  and sensor is broken)
		 */
		bool updateValue();
	private:
		/*
		 * value of long range finder
	     */
		double m_value;
};

#endif /* LASERRANGEFINDER_H_ */
