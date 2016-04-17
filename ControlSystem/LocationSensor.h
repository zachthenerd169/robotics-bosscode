/*
 * LocationSensor.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 *
 * Class Description: ImageCollector captures an image and stores it using the OpenCV libraries
 */

#ifndef LOCATIONSENSOR_H_
#define LOCATIONSENSOR_H_

class ImageCollector : Sensor
{
	public:
		/**
		 * Description: returns image as a char array
		 * Input: none
		 * Output: image encoded into a char array
		 */
		std::string readCurrentValue();
		/**
		 * Description: captures and image and stores it in m_Image
		 * Input: none
		 * Output: true if it could successfully capture the image, false otherwise
		 */
		bool updateValue();
	private:
		/**
		 * Image from openCV library
		 */
		//Image m_Image
		/**
		 * Camera to take the picture (might not need this)
		 */
		//Camera m_Camera
};



#endif /* LOCATIONSENSOR_H_ */
