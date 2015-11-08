/** -----------------------------------------------------------------------------
 * @file
 * @author Mathews Jacob & Amanda Beadle
 * @brief Partial solution to homework 5 (missing documentation)
 * Complying on Linux: g++ hw5.cpp Image.cpp EasyBMP/EasyBMP.cpp -o hw5.exe
 * Running .exe file: ./blemish_teeth.bmp (name of output image) (type of operation)
 */
#include "Image.h"
#include "PixelLocation.h"
#include <iostream>
#include <stack>
#include <cmath>
#include <iostream>

// possible function prototypes
/***************************************************************************************
* @brief Function that compute a component of the image that is connected to the pixel
*        indexed by seedRow and seedCol and has the same value as the seedPixel and inserts
*        the surrounding pixels with the same value into a stack.
* @param image
* @param seedRow
* @param seedCol
* @param ccLabel
***************************************************************************************/
static void markConnectedComponent(Image & image, const int seedRow, const int seedCol, const int ccLabel);

/***************************************************************************************
* @brief Function to adaptive smooth the image
*
* @param image:  InputImage
* @param sigma:  standard deviation of the noise (default value is 20)
* @param factor: Strength of smoothing (default value is 0.2)
*
* @return image: smoothed image
 ***************************************************************************************/
static Image smoothAdaptive(const Image & image, const double sigma=20, const double factor = 0.2);

/***************************************************************************************
 * @brief Function to smooth the image
 *
 * @param image:  InputImage
 * @param alpha: Strength of smoothing (default value is 0.2)
 *
 * @return image: smoothed image
 ***************************************************************************************/
static Image smooth(const Image & image, const float alpha=0.2);

/***************************************************************************************
* @brief The main function call
*
* @param argc  The number of arguments provided on the command line
* @param argv[] The vector of character strings from the command line
*
* @return 0 if no errors occured
 ***************************************************************************************/

int main( int argc, char* argv[] )
{
  // get input/output image file names (and threshold) from command line
  if( argc != 4 )
    {
        std::cout << "Usage instructions: " << std::endl;
        std::cout << "> hw5.exe inputImageFileName.bmp outputImage.bmp processtype ('smooth'/'asmooth'/'restore')"
              << std::endl;
        return -1;
    }
  const std::string inputImageFileName(argv[1]);

  // read input image
  std::cout << "Reading input image: " << inputImageFileName << std::endl;
  Image      myImage;
  const bool success = myImage.readFromBMPFile(inputImageFileName);
  if( !success )
    {
        std::cout << "Error reading input image." << std::endl;
        return -1;
    }
  const std::string outputImageFileName(argv[2]);

    std::cout << "Image Size " << myImage.getNumRows() << " " << myImage.getNumCols() << std::endl;
    
    Image processedImage(myImage);
    
    
  if( strcmp(argv[3], "smooth") == 0 ) // Smoothing
    {
        int iter;
        std::cout << "Smoothing: Enter number of iterations" << std::endl;
        std::cin >> iter;

        std::cout << "Smoothing the image: " << std::endl;
        for( int i = 1; i < iter; ++i )// smooths the image which ever amount of iterations that are inputed.
        {
            processedImage = smooth(processedImage);
        }

    }
    
  /* Adaptive smoothing */

  else if( strcmp(argv[3], "asmooth") == 0 )
    {                                       // Adaptive Smoothing
        int iter;
        int sigma;
        std::cout << "Adaptive smoothing: Enter number of iterations and noise variance" << std::endl;
        std::cin >> iter >> sigma;

        std::cout << "Adaptive Smoothing the image: " << inputImageFileName << std::endl;
        for( int i = 1; i < iter; ++i )
        {
          processedImage = smoothAdaptive(processedImage, sigma);
        }
    }
    
    
  else   // Blemish removal
    {
        const int seedRow = 168;
        const int seedCol = 343;
        
        // Threshold
        int threshold;
        std::cout << "This will take the image blemish_teeth.bmp and removes the pimple"<<std::endl;
        std::cout << "Enter threshold thirty-five works best " << std::endl;
        std::cin >> threshold;
        
        // Number of iterations
        const int iter = 300;
        int i = 0; //counter
       
        Image mask(processedImage);//mask with correct threshold
        mask -= processedImage.getPixel(seedRow,seedCol);//subtracts the values of the pixel
        mask.threshold(threshold);
        markConnectedComponent(mask, seedRow, seedCol, 1);//gets the values of all the pixels of the pimple.
        mask.setAllPixelsWithOldValToNewVal(254, 0);//sets all values that are 254 to 0.

        Image nonmask(mask);
        nonmask.logicalNot(); //replaces the mask pixel values from 1 to 0 or vice versa.
        
        Image smoothed(myImage);
        Image orginal(myImage);
        
        orginal *= nonmask;//convolves the inverted mask
    
        for (i=0; i<iter; i++) {

            smoothed = smooth(smoothed);
            smoothed *= mask;//convolves the smoothed image with only the mask
            smoothed += orginal;//adds the two together

        }
        processedImage = smoothed;
    }//end else statement
    
    std::cout << "Writing final image: " << outputImageFileName << std::endl;
    processedImage.writeToBMPFile(outputImageFileName);
    
    
  return 0;
}

    /***************************************************************************************
     * Function: smoothAdaptive
     * @brief Function to adaptive smooth the image
     *
     * @param image:  InputImage
     * @param sigma:  standard deviation of the noise (default value is 20)
     * @param factor: Strength of smoothing (default value is 0.2)
     *
     * @return image: smoothed image
     ***************************************************************************************/

Image smoothAdaptive(const Image & image, const double sigma, const double alpha)
{
  Image smoothedImage(image.getNumRows(), image.getNumCols() );

  for( int r = 0; r < image.getNumRows(); ++r )
    {
    for( int c = 0; c < image.getNumCols(); ++c )
      {
      const double rightDifference = (image.getPixel(r, c + 1) - image.getPixel(r, c) );
      const double leftDifference  = (image.getPixel(r, c - 1) - image.getPixel(r, c) );
      const double topDifference   = (image.getPixel(r + 1, c) - image.getPixel(r, c) );
      const double downDifference  = (image.getPixel(r - 1, c + 1) - image.getPixel(r, c) );

      const double alphaRight = alpha * exp(-rightDifference * rightDifference / sigma / sigma);
      const double alphaLeft  = alpha * exp(-leftDifference * leftDifference / sigma / sigma);
      const double alphaTop   = alpha * exp(-topDifference * topDifference / sigma / sigma);
      const double alphaDown  = alpha * exp(-downDifference * downDifference / sigma / sigma);

      double pixel  = (1.0 - alphaRight - alphaLeft - alphaTop - alphaDown) * image.getPixel(r, c);
      pixel += alphaRight * image.getPixel(r, c + 1);
      pixel += alphaLeft * image.getPixel(r, c - 1);
      pixel += alphaTop * image.getPixel(r + 1, c);
      pixel += alphaDown * image.getPixel(r - 1, c);

      smoothedImage.setPixel(r, c, pixel);
      }
    }

  return smoothedImage;
}

    /***************************************************************************************
     * Function: smooth()
     * Created By Amanda Beadle on 4.20.2015
     * @brief A function that will smooth the image from given input.
     *
     * @param image:  InputImage
     * @param alpha: Strength of smoothing (default value is 0.2)
     *
     * @return image: smoothed image
     ***************************************************************************************/

Image smooth(const Image & image, const float alpha)
{
    Image smoothedImage(image.getNumRows(), image.getNumCols() );
    
    for( int r = 0; r < image.getNumRows(); ++r )
    {
        for( int c = 0; c < image.getNumCols(); ++c )
        {
            double pixel = (1-4*alpha)*image.getPixel(r, c)
            + alpha * (image.getPixel(r, c + 1)//right pixel
                    + image.getPixel(r, c - 1)//left pixel
                    + image.getPixel(r + 1, c)//top pixel
                    + image.getPixel(r - 1, c));//bottom pixel
            
            smoothedImage.setPixel(r, c, pixel);
        }
    }//moves through the image pixel by pixel
    
    return smoothedImage;
}//end image smooth

    /*****************************************************************************************
     * Function: markConnectedComponent
     * Created By Amanda Beadle on 4.21.2015
     * @brief Function that compute a component of the image that is connected to the pixel
     *        indexed by seedRow and seedCol and has the same value as the seedPixel and inserts
     *        the surrounding pixels with the same value into a stack.
     * @param image
     * @param seedRow
     * @param seedCol
     * @param ccLabel
     *****************************************************************************************/
static void markConnectedComponent(Image & image, const int seedRow, const int seedCol, const int ccLabel)
{
    std::stack< PixelLocation > pixelLocStack;
    int intensity = 254;
    
    PixelLocation pixel;
    pixel.SetRow(seedRow);
    pixel.SetCol(seedCol);
    
    pixelLocStack.push(pixel);//pushes the first location onto the stack
    
    while (! pixelLocStack.empty() )
    {
        PixelLocation toppixel = pixelLocStack.top();
        pixelLocStack.pop();//takes the first pixel location from the stack and iterates through until it is empty
 
        int valueOfPixel = image.getPixel(toppixel.GetRow(), toppixel.GetCol());
        //gets value of pixel from orignal image
        
        if( valueOfPixel == intensity)
        {
            image.setPixel(toppixel.GetRow(), toppixel.GetCol(), ccLabel);//cclabel sets the pixel value to 1.
  
            PixelLocation pixel_below(toppixel.GetRow() + 1, toppixel.GetCol());
            pixelLocStack.push(pixel_below);//puts the pixel below toppixel on to the stack.
            
            PixelLocation pixel_above(toppixel.GetRow() - 1, toppixel.GetCol());
            pixelLocStack.push(pixel_above);
            
            PixelLocation pixel_right(toppixel.GetRow(), toppixel.GetCol() + 1);
            pixelLocStack.push(pixel_right);
            
            PixelLocation pixel_left(toppixel.GetRow(),toppixel.GetCol()- 1);
            pixelLocStack.push(pixel_left);
            
         }
    }
}//end markedConnectedComponents

