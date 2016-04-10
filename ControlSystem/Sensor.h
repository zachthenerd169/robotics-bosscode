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
		virtual void * readCurrentValue();
		virtual  bool updateValue() = 0;

	private:
		//DataBuffer* m_databuffer;
};




#endif /* SENSOR_H_ */
