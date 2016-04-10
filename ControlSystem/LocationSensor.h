/*
 * LocationSensor.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 */

#ifndef LOCATIONSENSOR_H_
#define LOCATIONSENSOR_H_

class ImageCollector : Sensor
{
	public:
		std::string readCurrentValue();
		bool updateValue();
	private:
		double m_x;
		double m_y;
};



#endif /* LOCATIONSENSOR_H_ */
