/*
 * LasorRangeFinder.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 */

#ifndef LASORRANGEFINDER_H_
#define LASORRANGEFINDER_H_

class LasorRangeFinder : Sensor
{
	public:
		std::string readCurrentValue();
		bool updateValue();
	private:
		double m_value;
};

#endif /* LASORRANGEFINDER_H_ */
