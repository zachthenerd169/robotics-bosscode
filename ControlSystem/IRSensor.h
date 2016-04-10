/*
 * IRSensor.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 */

#ifndef IRSENSOR_H_
#define IRSENSOR_H_


class IRSensor : Sensor
{
	public:
		std::string readCurrentValue();
		bool updateValue();
	private:
		double m_value;
};


#endif /* IRSENSOR_H_ */
