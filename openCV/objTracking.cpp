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
using namespace cv;
using namespace std;

struct ImageData
{
    Mat image;
    Mat filtered_image;
    Rect object;
    ImageData() {}
    ImageData(Mat i1, Mat i2, Rect o)
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
        cap = VideoCapture(0);
        if(!cap.isOpened())
        {
            cout << "Cannot open webcam" << endl;
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
        Mat filteredImage;
        cameraImage.copyTo(filteredImage);
        applyThreshold(filteredImage);
        applyFilter(filteredImage);
        Rect largestRectangle;
        if(findLargestObjectBoundingRectangle(filteredImage, largestRectangle) == -1)
        {
            largestRectangle = Rect(0,0,0,0);
        }

        return ImageData(cameraImage, filteredImage, largestRectangle);
    }
private:
    VideoCapture cap;

    Mat cameraImage;
public:
    Threshold tHue;
    Threshold tSat;
    Threshold tVal;
private:
    void applyThreshold(Mat &inputOutputImage)
    {
        cvtColor(inputOutputImage, inputOutputImage, COLOR_BGR2HSV);

        inRange(inputOutputImage, Scalar(tHue.low,tSat.low,tVal.low), Scalar(tHue.high,tSat.high,tVal.high), inputOutputImage);
    }

    void applyFilter(Mat &inputOutputImage)
    {
        morphologyEx(inputOutputImage, inputOutputImage, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
        morphologyEx(inputOutputImage, inputOutputImage, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
    }

    int findLargestObjectBoundingRectangle(const Mat &inputImage, Rect &outputRect)
    {
        typedef vector<vector<Point>> ContourType;
        typedef vector<Vec4i>         HierarachyType;

        ContourType contours;
        HierarachyType hierarachy;

        Mat tmpImage;
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
        cout << "could not init improc" << endl;
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
    namedWindow("ThresholdValues", CV_WINDOW_NORMAL);
    cvCreateTrackbar("LowH", "ThresholdValues", &improc.tHue.low, 179);
    cvCreateTrackbar("HighH", "ThresholdValues", &improc.tHue.high, 179);
    cvCreateTrackbar("LowS", "ThresholdValues", &improc.tSat.low, 255);
    cvCreateTrackbar("HighS", "ThresholdValues", &improc.tSat.high, 255);
    cvCreateTrackbar("LowV", "ThresholdValues", &improc.tVal.low, 255);
    cvCreateTrackbar("HighV", "ThresholdValues", &improc.tVal.high, 255);
    

    namedWindow("CameraImage", CV_WINDOW_NORMAL);
    namedWindow("FilterImage", CV_WINDOW_NORMAL);

    zwlib::ContinuousUpdater<ImageData> cu(&improc,std::chrono::milliseconds(50));

    cu.start();

    while(!cu.ready()) {}

    while(waitKey(1) == -1)
    {
        ImageData data = cu.get();
        Mat image = data.image;
        Mat threshImage = data.filtered_image;

        Scalar lineColor(0,255,0);
        int lineWidth = 2;
        double area = data.object.width * data.object.height;
        double meanLength = sqrt(area);

        circle(
            image, 
            Point(data.object.x+data.object.width/2, data.object.y+data.object.height/2), 
            meanLength/2, 
            lineColor, lineWidth
        );
        line(
            image, 
            Point(data.object.x, data.object.y+data.object.height/2), 
            Point(data.object.x+data.object.width, data.object.y+data.object.height/2), 
            lineColor, lineWidth
        );
        line(
            image, 
            Point(data.object.x+data.object.width/2, data.object.y), 
            Point(data.object.x+data.object.width/2, data.object.y+data.object.height), 
            lineColor, lineWidth
        );

        imshow("CameraImage", image);
        imshow("FilterImage", threshImage);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
