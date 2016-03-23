/* http://www.imagemagick.org/api/Image++.php */
/***********************************************
 The sample code below demonstrates reading images,
 resizing them, and making them grayscale for the
 purpose of sending over a socket. This will not
 compile yet
 **********************************************/

#include <Magick++.h>
#include <iostream>
using namespace Magick;


Camera::Camera(char **argv)
{
    InitializeMagick(*argv);
}

Camera::ReadImage(char* imageName)
{
    // Construct the image object. Separating image construction from the
    // the read operation ensures that a failure to read the image file
    // doesn't render the image object useless.
    testImage;
    try {
        // Read a file into image object
        testImage.read( "girl.gif" );
    }
    catch( Exception &error_ )
    {
        std::cout << "Caught exception: " << error_.what() << endl;
        return 1;
    }
}

Camera::CompressImage(char* resolution)
{
    // Resize the image to save data (e.g. "640x480")
    testImage.resize(resolution);
    
    // Convert the image to grayscale to save data
    testImage.quantizeColorSpace(GRAYColorspace);
    testImage.quantizeColors(256);
    image.quantize();
}

