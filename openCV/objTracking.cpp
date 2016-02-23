#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/videoio/videoio.hpp"
#include <string>
#include "ContinuousUpdater.h"

/**
 
 * To Compile: g++ -o objTracking.exe objTracking.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui  -lopencv_videoio
 
 * To Run: ./objTracking.exe
 
 **/
using namespace cv;
using namespace std;

struct ImageData
{
    vector<Mat> images;
    vector<Rect> objects;
    ImageData(vector<Mat> i, vector<Rect> o)
    {
        images = i;
        objects = o;
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

        tHue.low = 106;
        tHue.high = 126;
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
        Rect largestRectangle = findLargestObjectBoundingRectangle(filteredImage);

        vector<Mat> images =  {cameraImage, filteredImage};
        vector<Rect> objects = {largestRectangle};

        return ImageData(images, objects);
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
        inputOutputImage = morphologyEx(inputOutputImage, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        inputOutputImage = morphologyEx(inputOutputImage, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    }

    Rect findLargestObjectBoundingRectangle(const Mat &inputImage)
    {
        typedef vector<vector<Point>> ContourType;
        typedef vector<Vec4i>         HierarachyType;

        ContourType contours;
        HierarachyType hierarachy;

        findContours(inputImage, contours, hierarachy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        double largestArea = 0;
        int indexOfLargestContour = 0;
        for (int i = 0; i < contours.size(); ++i)
        {
            double currentArea = contourArea(contours[i], false);
            if(currentArea > largestArea)
            {
                currentArea = largestArea;
                indexOfLargestContour = i;
            }
        }

        return boundingRect(contours[indexOfLargestContour]);
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


    namedWindow("ThresholdValues", CV_WINDOW_NORMAL);
    cvCreateTrackbar("LowH", "ThresholdValues", &improc.tHue.low, 179);
    cvCreateTrackbar("HighH", "ThresholdValues", &improc.tHue.high, 179);
    cvCreateTrackbar("LowS", "ThresholdValues", &improc.tSat.low, 255);
    cvCreateTrackbar("HighS", "ThresholdValues", &improc.tSat.high, 255);
    cvCreateTrackbar("LowV", "ThresholdValues", &improc.tVal.low, 255);
    cvCreateTrackbar("HighV", "ThresholdValues", &improc.tVal.high, 255);


    namedWindow("CameraImage", CV_WINDOW_NORMAL);
    imshow("CameraImage", improc.update().images[0]);

    zwlib::ContinuousUpdater<ImageData> cu(&improc,std::chrono::milliseconds(50));

    cu.start();

    while(!cu.ready()) {}

    while(waitKey(1) == -1)
    {
        ImageData data = cu.get();
        Mat image = data.images[0];

        Scalar lineColor(0,255,0);
        int lineWidth = 2;

        circle(
            image, 
            Point(data.objectX, data.objectY), 
            data.objectWidth/4, 
            lineColor, lineWidth
        );
        line(
            image, 
            Point(data.objectX-data.objectWidth/2, data.objectY), 
            Point(data.objectX-data.objectWidth/2, data.objectY), 
            lineColor, lineWidth
        );
        line(
            image, 
            Point(data.objectX, data.objectY-data.objectHeight/2), 
            Point(data.objectX, data.objectY+data.objectHeight/2), 
            lineColor, lineWidth
        );

        imshow("CameraImage", image);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}


int old_main(int argc, char** argv)
{
    VideoCapture cap(0); // capture the video from web cam
    
    
    
    if (!cap.isOpened()) // if not success exit program
    {
        cout<< "Cannot open the Web cam" <<endl;
        return -1;
    }
    namedWindow("Control" ,CV_WINDOW_NORMAL); // create a window called "control"
    
    int iLowH,iHighH,iLowS,iHighS,iLowV,iHighV;
  
    
    cvCreateTrackbar("LowH", "Control", &iLowH, 179);
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);
    
    cvCreateTrackbar("LowS", "Control", &iLowS, 255);
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);
    
    cvCreateTrackbar("LowV", "Control", &iLowV, 255);
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);
    
    /*int iLowH= 100;
    int iHighH=140;//pure red is at 120 angle
    int iLowS=230;//
    int iHighS=255;//
    int iLowV=230;//
    int iHighV=250;//*/
    
    
    while (true)
    {
        Mat imgOriginal;
        
        bool bSuccess = cap.read(imgOriginal); // read a new frame from video
        
        if (!bSuccess)
        {
            cout<< "Cannnot read a frame video from stream" << endl;
            break;
        }
        
        Mat imgHSV;
        
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); // convert bgr to hsv
        
        Mat imgThresholded;
        
        inRange(imgHSV, Scalar(iLowH,iLowS,iLowV), Scalar(iHighH,iHighS,iHighV), imgThresholded);
        
        //morphological opening (remove small objects from foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        dilate (imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        
        
        //morphological closing (fill small holes in the foreground)
        dilate (imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        
        searchForMovement(imgThresholded, imgOriginal);
        
        namedWindow ("Thresholded Image", WINDOW_NORMAL);
        namedWindow ("Original", WINDOW_NORMAL);
        namedWindow ("HSVImage", WINDOW_NORMAL);
        
        
        //imshow("Thresholded Image", imgThresholded);
        //imshow("Original", imgOriginal);
        //imshow("HSVImage", imgHSV);
        
	imshow("Thresholded Image", imgThresholded);
	imshow("Original", imgOriginal);
	imshow("HSVImage", imgHSV);

   	if (waitKey(1) != -1)// wait for 'esc' key press for 30ms. If 'esc' pressed break the loop
    	{
        	cout<<"esc key is pressed by user" <<endl;
        	break;
    	}
    }
    
    return 0;
}
