#include "../ImageCollector.h"

ImageCollector()
{
	camera = cv::VideoCapture(0);
    if(!camera.isOpened())
    {
    	std::cerr << "Cannot open webcam" << std::endl;
        exit(1);
    }
}

std::string ImageCollector::readCurrentValue()
{
	return "";
}
bool ImageCollector::updateValue()
{
	return false;
}