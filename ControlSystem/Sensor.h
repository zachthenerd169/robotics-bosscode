/*
 * Sensor.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 * Class description: base class for all of the sensors
 */

#ifndef SENSOR_H_
#define SENSOR_H_

class Sensor
{
	public:
		virtual ~Sensor(){};
		/**
		 * Description: getting a reading from the sensor
		 * Inputs: none
		 */
		virtual std::string readCurrentValue() = 0;
		/**
		 * Description: updating its current sensor value (this value will then
		 * 				be written to a buffer if requested
		 * Inputs: none
		 */
		virtual  bool updateValue() = 0;
};




#endif /* SENSOR_H_ */
