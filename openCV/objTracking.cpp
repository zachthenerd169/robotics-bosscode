#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/videoio/videoio.hpp"
#include <string>

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

int main(int argc, char** argv)
{
    int iLowH,iHighH,iLowS,iHighS,iLowV,iHighV;
    VideoCapture camera(0); //opens the default camera
    
    if (!camera.isOpened()) //if not success exit program
    {
        cout<< "Cannot open the Web cam" <<endl;
        return -1;
    }
    namedWindow("ObjDetect" ,CV_WINDOW_NORMAL); //create a window called "obj_dectection"
    
    //int cvCreateTrackbar(const char* trackbarName, const char* windowName, int* value, int count, CvTrackbarCallback onChange)
    //can use trackbar to of HSV variables
    
    cvCreateTrackbar("LowH", "Control", &iLowH, 179);
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);
    
    cvCreateTrackbar("LowS", "Control", &iLowS, 255);
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);
    
    cvCreateTrackbar("LowV", "Control", &iLowV, 255);
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);
    
    //hard coding HSV values
    /*int iLowH= 100;
    int iHighH=140;
    int iLowS=230;
    int iHighS=255;
    int iLowV=230;
    int iHighV=250;*/
    
    while (true)
    {
        Mat inputFrame; //creating an empty matrix
        Mat hsvFrame; //creating an empty matrix
        Mat mask;
        
        bool bSuccess = camera.read(inputFrame); //read a new frame from video and store it in Mat (read in as a BRG image)
        if (!bSuccess)
        {
            cout<< "Cannnot read a frame video from stream" << endl;
            break; //exit while loop
        }
        cvtColor(inputFrame, imgHSV, COLOR_BGR2HSV); //convert BGR to HSV
        
        //Checks if array elements lie between the elements of two other arrays.
        //(InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst)
        
        
        inRange(hsvFrame, Scalar(iLowH,iLowS,iLowV), Scalar(iHighH,iHighS,iHighV), mask); //if HSV pixel lies in the range; the pixel becomes 255 (1) otherwise the pixel is 0
        
        //morphological opening (remove small objects from foreground)
        //erodes away the boundaries of foreground objects
        //useful for removing small white objects
        erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        //growing the image again
        dilate (mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        //why do this twice??
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
        
        for (int i=0; i<3; i++)
        {
            switch (i) {
                case 1:
                    imshow("Thresholded Image", imgThresholded);
                    break;
                case 2:
                    imshow("Original", imgOriginal);
                    if (waitKey(30) == 30)// wait for 'esc' key press for 30ms. If 'esc' pressed
                    break;
                case 3:
                    imshow("HSVImage", imgHSV);
                    break;
                    
                default:
                    break;
            }
        
        
        if (waitKey(30) == 27)// wait for 'esc' key press for 30ms. If 'esc' pressed break the loop
        {
            cout<<"esc key is pressed by user" <<endl;
            break;
        }
            }

    
    }
    
    return 0;
    
}

