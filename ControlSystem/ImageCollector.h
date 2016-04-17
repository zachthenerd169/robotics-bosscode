/*
 * ImageCollector.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 */

#ifndef IMAGECOLLECTOR_H_
#define IMAGECOLLECTOR_H_

class LocationSensor : Sensor
{
	public:
		/**
		 * Description: returns m_x & m_y stored in a string format
		 * Input: none
		 * Output: string format of m_x and m_y
		 * 			EX) "{'x': 0, 'y': 0}" (using JSON format)
		 */
		std::string readCurrentValue();
		/**
		 * Description: analyzes the Image from the ImageCollector to determine the
		 * 				robot's location. stores this location in m_x & m_y
		 * Input: none
		 * Output: true if successfully found and stored location, false otherwise
		 */
		bool updateValue();
	private:
		/**
		 * y coordinate of the robot's camera relative to the bucket
		 */
		double m_x;
		/**
		 * x coordinate of the robot's camera relative to the bucket
		 */
		double m_y;
};

#endif /* IMAGECOLLECTOR_H_ */
