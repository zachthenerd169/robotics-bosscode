#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/videoio/videoio.hpp"
#include <string>
#include <math.h>
#include "ContinuousUpdater.h"
#include "ConfigReader.h"

/**
 
 * To Compile: g++ -o objTracking.exe objTracking.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui  -lopencv_videoio
 
 * To Run: ./objTracking.exe
 
 **/

struct ImageData
{
    cv::Mat image;
    cv::Mat filtered_image;
    cv::Rect object;
    ImageData() {}
    ImageData(cv::Mat i1, cv::Mat i2, cv::Rect o)
    {
        image = i1;
        filtered_image = i2;
        object = o;
    }
};

/* encapsulate image processing into an object */
class ImageProc : public zwlib::IUpdater<ImageData>
{
    struct Threshold
    {
        int low;
        int high;
    };
public:
    int init()
    {
        cap = cv::VideoCapture(0);
        if(!cap.isOpened())
        {
            std::cout << "Cannot open webcam" << std::endl;
            return -1;
        }

        tHue.low = 0;
        tHue.high = 179;
        tSat.low = 68;
        tSat.high = 255;
        tVal.low = 60;
        tVal.high = 255;
    }

    ImageData update()
    {
        cap.read(cameraImage);
        cv::Mat filteredImage;
        cameraImage.copyTo(filteredImage);
        applyThreshold(filteredImage);
        applyFilter(filteredImage);
        cv::Rect largestRectangle;
        if(findLargestObjectBoundingRectangle(filteredImage, largestRectangle) == -1)
        {
            largestRectangle = cv::Rect(0,0,0,0);
        }

        return ImageData(cameraImage, filteredImage, largestRectangle);
    }
private:
    cv::VideoCapture cap;

    cv::Mat cameraImage;
public:
    Threshold tHue;
    Threshold tSat;
    Threshold tVal;
private:
    void applyThreshold(cv::Mat &inputOutputImage)
    {
        cvtColor(inputOutputImage, inputOutputImage, cv::COLOR_BGR2HSV);

        inRange(inputOutputImage, cv::Scalar(tHue.low,tSat.low,tVal.low), cv::Scalar(tHue.high,tSat.high,tVal.high), inputOutputImage);
    }

    void applyFilter(cv::Mat &inputOutputImage)
    {
        morphologyEx(inputOutputImage, inputOutputImage, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10)));
        morphologyEx(inputOutputImage, inputOutputImage, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10)));
    }

    int findLargestObjectBoundingRectangle(const cv::Mat &inputImage, cv::Rect &outputRect)
    {
        typedef std::vector<std::vector<cv::Point>> ContourType;
        typedef std::vector<cv::Vec4i>         HierarachyType;

        ContourType contours;
        HierarachyType hierarachy;

        cv::Mat tmpImage;
        inputImage.copyTo(tmpImage);

        findContours(tmpImage, contours, hierarachy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        double largestArea = 0;
        int indexOfLargestContour = 0;
        for (int i = 0; i < contours.size(); ++i)
        {
            double currentArea = contourArea(contours[i], false);
            if(currentArea > largestArea)
            {
                largestArea = currentArea;
                indexOfLargestContour = i;
            }
        }
	
	if(contours.size() == 0)
        {
            return -1;
        }	
        outputRect = boundingRect(contours[indexOfLargestContour]);

        return 1;
    }
};

/* new main function that tests using the image processing object
 * with the multithreadded updater
 */
int main(int argc, char* argv[])
{   
    ImageProc improc;
    if(improc.init() == -1)
    {
        std::cout << "could not init improc" << std::endl;
        return -1;
    }

    ConfigReader settings("../data/config.txt");

    if(settings.has("threshold_hue_low"))
    {
      improc.tHue.low = std::stoi(settings.get("threshold_hue_low"));
    }
    if(settings.has("threshold_hue_high"))
    {
      improc.tHue.high = std::stoi(settings.get("threshold_hue_high"));
    }
    if(settings.has("threshold_sat_low"))
    {
      improc.tSat.low = std::stoi(settings.get("threshold_sat_low"));
    }
    if(settings.has("threshold_sat_high"))
    {
      improc.tSat.high = std::stoi(settings.get("threshold_sat_high"));
    }
    if(settings.has("threshold_val_low"))
    {
      improc.tVal.low = std::stoi(settings.get("threshold_val_low"));
    }
    if(settings.has("threshold_val_high"))
    {
      improc.tVal.high = std::stoi(settings.get("threshold_val_high"));
    }
    cv::namedWindow("ThresholdValues", CV_WINDOW_NORMAL);
    cvCreateTrackbar("LowH", "ThresholdValues", &improc.tHue.low, 179);
    cvCreateTrackbar("HighH", "ThresholdValues", &improc.tHue.high, 179);
    cvCreateTrackbar("LowS", "ThresholdValues", &improc.tSat.low, 255);
    cvCreateTrackbar("HighS", "ThresholdValues", &improc.tSat.high, 255);
    cvCreateTrackbar("LowV", "ThresholdValues", &improc.tVal.low, 255);
    cvCreateTrackbar("HighV", "ThresholdValues", &improc.tVal.high, 255);
    

    cv::namedWindow("CameraImage", CV_WINDOW_NORMAL);
    cv::namedWindow("FilterImage", CV_WINDOW_NORMAL);

    zwlib::ContinuousUpdater<ImageData> cu(&improc,std::chrono::milliseconds(50));

    cu.start();

    while(!cu.ready()) {}

    while(cv::waitKey(1) == -1)
    {
        ImageData data = cu.get();
        cv::Mat image = data.image;
        cv::Mat threshImage = data.filtered_image;

        cvtColor(image, image, cv::COLOR_BGR2HSV);
	cv::Scalar avgColor= cv::mean(image,threshImage);
        cvtColor(image, image, cv::COLOR_HSV2BGR);
	std::cout << avgColor << std::endl;
	if(data.object.width * data.object.height > 2000) // only adjust if target is large enough. 2000 is ~ 2/3 of the full size at ~ 5m
	{
            improc.tHue.low = (improc.tHue.low*99 + avgColor[0] - 20)/100;
            improc.tHue.high = (improc.tHue.high*99 + avgColor[0] + 20)/100;
            improc.tSat.low = (improc.tSat.low*99 + avgColor[1] - 90)/100;
            improc.tSat.high = (improc.tSat.high*99 + avgColor[1] + 90)/100;
            improc.tVal.low = (improc.tVal.low*99 + avgColor[2] - 20)/100;
            improc.tVal.high = (improc.tVal.high*99 + avgColor[2] + 20)/100;
            std::cout << "adjusting threshold" << std::endl;
            std::cout << "[<" << improc.tHue.low << "," << improc.tHue.high << ">,";
            std::cout << "<" << improc.tSat.low << "," << improc.tSat.high << ">,";
            std::cout << "<" << improc.tVal.low << "," << improc.tVal.high << ">]" << std::endl;
	}

        cv::Scalar lineColor(0,255,0);
        int lineWidth = 2;
        double area = data.object.width * data.object.height;
        double meanLength = sqrt(area);

        circle(
            image, 
            cv::Point(data.object.x+data.object.width/2, data.object.y+data.object.height/2), 
            meanLength/2, 
            lineColor, lineWidth
        );
        line(
            image, 
            cv::Point(data.object.x, data.object.y+data.object.height/2), 
            cv::Point(data.object.x+data.object.width, data.object.y+data.object.height/2), 
            lineColor, lineWidth
        );
        line(
            image, 
            cv::Point(data.object.x+data.object.width/2, data.object.y), 
            cv::Point(data.object.x+data.object.width/2, data.object.y+data.object.height), 
            lineColor, lineWidth
        );

        imshow("CameraImage", image);
        imshow("FilterImage", threshImage);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
