/*
 * LocationSensor.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 *
 * Class Description: ImageCollector captures an image and stores it using the OpenCV libraries
 */
#ifndef IMAGECOLLECTOR_H_
#define IMAGECOLLECTOR_H_

#include <iostream>
// #include "opencv2/highgui.hpp"
// #include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/videoio/videoio.hpp"

 using namespace cv;

class ImageCollector : public Sensor
{
	public:

		/**
		 * Description: constructor initializes webcam
		 *
		 */
		ImageCollector();
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
		/**
		 * will probably want a function like this for LocationSensor
		 */
		//Image getImage();
	private:
		/**
		 * Image from openCV library
		 */
		//Image m_Image
		/**
		 * Camera to take the picture (might not need this)
		 */
		VideoCapture m_camera;
};



#endif /* LOCATIONSENSOR_H_ */
