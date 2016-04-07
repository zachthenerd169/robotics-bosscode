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




int theObject[2] = {0,0};

//bounding the rectangle of object, we will use the center of it as its position
Rect objectBoundingRectangle = Rect(0,0,0,0);

//
void searchForMovement (Mat thresholdImage, Mat &cameraFeed)
{
    
    bool objectDetected = false;
    Mat temp;
    thresholdImage.copyTo(temp);
    
    //These two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarachy;
    
    findContours( temp, contours, hierarachy, CV_RETR_EXTERNAL ,CV_CHAIN_APPROX_SIMPLE);
    //if contours vector is not empty we have found some objects
    if (contours.size() > 0)objectDetected=true;
    else objectDetected = false;
    if (objectDetected){
        //the largest contour is found at the end of the contours vector
        //we will assume that the biggest contour is the object we are looking for
        vector< vector<Point> > largestContourVec;
        largestContourVec.push_back(contours.at(contours.size() - 1));
        objectBoundingRectangle = boundingRect(largestContourVec.at(0));
        
        //make a bounding rectangle around the largest contour then find its centeroid
        //this will be the object's final estimated position
        int xpos= objectBoundingRectangle.x + objectBoundingRectangle.width / 2;
        int ypos= objectBoundingRectangle.y + objectBoundingRectangle.height /2;
        
        //update the object position by changing the 'theObject values'
        theObject[0] = xpos, theObject[1]=ypos;
    
    }
    //some temp x and y
    int x =theObject[0];
    int y=theObject[1];
    
    //draw some crosshairs on the object
    circle(cameraFeed, Point(x,y), 20, Scalar(0,255,0) , 2);
    line (cameraFeed, Point(x,y), Point(x,y-25), Scalar(0,255,0),2);
    line(cameraFeed, Point(x,y), Point(x,y+25), Scalar(0,255,0),2);
    line(cameraFeed, Point(x,y), Point(x-25,y), Scalar(0,255,0),2);
    line(cameraFeed, Point(x,y), Point(x+25,y), Scalar(0,255,0),2);
    //putText(cameraFeed, &"tracking object at ("+ x, Point(x,y), 1,1, Scalar(0,0,255), 2);
    
}

/* encapsulate image processing into an object */
class ImageProc : public zwlib::IUpdater<Mat>
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

    Mat update()
    {
        cap.read(cameraImage);
        return cameraImage;
    }
private:
    VideoCapture cap;

    Mat cameraImage;

public:
    Threshold tHue;
    Threshold tSat;
    Threshold tVal;
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

    namedWindow("CameraImage", CV_WINDOW_NORMAL);
    imshow("CameraImage", improc.update());

    zwlib::ContinuousUpdater<Mat> cu(&improc);

    cu.start();

    while(!cu.ready()) {}

    while(waitKey(1) == -1)
    {
        imshow("CameraImage", cu.get());
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
