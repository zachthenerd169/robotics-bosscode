/*
 * ImageCollector.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 */

#ifndef IMAGECOLLECTOR_H_
#define IMAGECOLLECTOR_H_

class ImageCollector : Sensor
{
	public:
		std::string readCurrentValue();
		bool updateValue();
	private:
		//Image m_image --> from openCV
};

#endif /* IMAGECOLLECTOR_H_ */
