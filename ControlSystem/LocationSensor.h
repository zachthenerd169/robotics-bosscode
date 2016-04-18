/*
 * ImageCollector.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 *
 * Class Description: LocationSensors reads in an image from ImageCollector, analyzes the image
 * 					  and then determines the robot's location relative to the collector bin from
 * 					  these images
 */

#ifndef LOCATIONSENSOR_H_
#define LOCATIONSENSOR_H_

class LocationSensor : public Sensor
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
		 * image collector so LocationSensor can analyze the image
		 */
		ImageCollector m_image_collector;
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
