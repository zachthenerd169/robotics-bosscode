/*
 * Sensor.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 */

#ifndef SENSOR_H_
#define SENSOR_H_

class Sensor
{
	public:
		virtual ~Sensor(){};
		virtual std::string readCurrentValue() = 0;
		virtual  bool updateValue() = 0;
};




#endif /* SENSOR_H_ */
