// ------------------------------------------------------------------------------
// Programmer: Mathews Jacob
// Name: Image.cpp
// Description: Implementation of member functions of Image class for homework 5
// -------------------------------------------------------------------------------
#include "Image.h"
#include "EasyBMP/EasyBMP.h"
#include <cstdlib>
#include <ctime>

Image::Image() :
  m_numRows(0),
  m_numCols(0),
  m_pixels(NULL)
{
}

Image::Image(int numRows, int numCols) :
  m_numRows(numRows),
  m_numCols(numCols)
{
  if( m_numRows * m_numCols > 0 )
    {
    m_pixels = new double[m_numRows * m_numCols];
    setAllPixels(0);
    }
  else
    {
    m_pixels = NULL;
    }
}

Image::Image(const Image & imageToCopyFrom)
{
  // copy rows/cols/pixels
  m_numRows = imageToCopyFrom.m_numRows;
  m_numCols = imageToCopyFrom.m_numCols;
  if( m_numRows * m_numCols > 0 )
    {
    m_pixels = new double[m_numRows * m_numCols];
    for( int i = 0; i < m_numRows * m_numCols; ++i )
      {
      m_pixels[i] = imageToCopyFrom.m_pixels[i];
      }
    }
  else
    {
    m_pixels = NULL;
    }
}

Image::~Image()
{
  if( m_pixels != NULL )
    {
    delete [] m_pixels;
    m_numRows = 0;
    m_numCols = 0;
    }
}

const Image & Image::operator=(const Image & imageOnRight)
{
  // avoid self-assignment
  if( &imageOnRight != this )
    {
    // if images have different sizes, delete old space and allocate new space
    if( m_numRows != imageOnRight.m_numRows || m_numCols != imageOnRight.m_numCols )
      {
      if( m_pixels != NULL )
        {
        delete [] m_pixels;
        m_pixels = NULL;
        }
      m_numRows = imageOnRight.m_numRows;
      m_numCols = imageOnRight.m_numCols;
      if( m_numRows * m_numCols > 0 )
        {
        m_pixels = new double[m_numRows * m_numCols];
        }
      }
    // now copy pixels
    for( int i = 0; i < m_numRows * m_numCols; ++i )
      {
      m_pixels[i] = imageOnRight.m_pixels[i];
      }

    }

  return *this;   // enables I1 = I2 = I3, for example
}

const Image & Image::operator+=(const Image & imageOnRight)
{
  // avoid self-assignment
  if( &imageOnRight != this )
    {
    // if images have different sizes, delete old space and allocate new space
    if( m_numRows != imageOnRight.m_numRows || m_numCols != imageOnRight.m_numCols )
      {
      std::cout << "Images not of same size; cannot add\n";
      return *this;
      }
    // now copy pixels
    for( int i = 0; i < m_numRows * m_numCols; ++i )
      {
      m_pixels[i] += imageOnRight.m_pixels[i];
      }

    }

  return *this;   // enables I1 = I2 = I3, for example
}

const Image & Image::operator*=(const Image & imageOnRight)
{
    // avoid self-assignment
    if( &imageOnRight != this )
    {
        // if images have different sizes, delete old space and allocate new space
        if( m_numRows != imageOnRight.m_numRows || m_numCols != imageOnRight.m_numCols )
        {
            std::cout << "Images not of same size; cannot add\n";
            return *this;
        }
        // now copy pixels
        for( int i = 0; i < m_numRows * m_numCols; ++i )
        {
            //std::cout << "pixelvalue "<< m_pixels[i] << "  "<<imageOnRight.m_pixels[i] << std::endl;
            m_pixels[i] = m_pixels[i] * imageOnRight.m_pixels[i];
        }
        
    }
    
    return *this;   // enables I1 = I2 = I3, for example
}

void Image::logicalNot()
{
        // now copy pixels
        for( int i = 0; i < m_numRows * m_numCols; ++i )
        {
            if(m_pixels[i] == 0)
                m_pixels[i] = 1;
            else
                m_pixels[i] = 0;
        }
    
    return;
}





bool Image::readFromBMPFile(const std::string & inputFileName)
{
  bool success = true;

  // use BMP object to read image
  BMP inputImage;

  success = inputImage.ReadFromFile(inputFileName.c_str() );
  if( success )
    {
    // allocate memory for image (deleting old, if exists)
    m_numRows = inputImage.TellHeight();
    m_numCols = inputImage.TellWidth();
    if( m_pixels != NULL )    // deallocate old memory
      {
      delete [] m_pixels;
      }
    m_pixels = new double[m_numRows * m_numCols];
    // copy pixels
    for( int r = 0; r < m_numRows; ++r )
      {
      for( int c = 0; c < m_numCols; ++c )
        {
        RGBApixel pixelVal = inputImage.GetPixel(c, r);
        double    val = (double) pixelVal.Blue + (double) pixelVal.Green + (double) pixelVal.Red;
        val = (val / 3.0 + 0.5);
        m_pixels[r * m_numCols + c] = val;
        }
      }
    }

  return success;
}

bool Image::writeToBMPFile(const std::string & outputFileName)
{
  bool success = true;

  if( m_pixels != NULL )
    {
    // create bitmap image
    BMP outputImage;
    outputImage.SetSize(m_numCols, m_numRows);
    outputImage.SetBitDepth( 24 );

    double maxVal = m_pixels[0];
    double minVal = m_pixels[0];
    // Maximum and minimum values
    for( int i = 1; i < m_numRows * m_numCols; ++i )
      {
      if( m_pixels[i] > maxVal )
        {
        maxVal = m_pixels[i];
        }
      if( m_pixels[i] <= minVal )
        {
        minVal = m_pixels[i];
        }
      }
    for( int r = 0; r < m_numRows; ++r )
      {
      for( int c = 0; c < m_numCols; ++c )
        {
        // get pixel value and clamp between 0 and 255
        double val = 255.0 * (m_pixels[r * m_numCols + c] - minVal) / (maxVal - minVal);

        if( val < 0 )
          {
          val = 0;
          }
        if( val > 255 )
          {
          val = 255;
          }
        // set output color based on mapping
        RGBApixel pixelVal;
        pixelVal.Blue = (int)val; pixelVal.Green = (int)val; pixelVal.Red = (int)val;
        outputImage.SetPixel(c, r, pixelVal);
        }
      }

    // write to file
    success = outputImage.WriteToFile( outputFileName.c_str() );

    }
  else
    {
    success = false;
    }

  return success;
}

double Image::getPixel(int r, int c) const
{

  r = (r < 0) ? 0 : (r >= m_numRows) ? m_numRows - 1 : r;
  c = (c < 0) ? 0 : (c >= m_numCols) ? m_numCols - 1 : c;

  return m_pixels[r * m_numCols + c];
}

bool Image::isInBounds(int r, int c) const
{
  return r >= 0 && r < m_numRows && c >= 0 && c < m_numCols;
}

int Image::getNumRows() const
{
  return m_numRows;
}

int Image::getNumCols() const
{
  return m_numCols;
}

void Image::setPixel(int r, int c, double val)
{
  if( isInBounds(r, c) )
    {
    m_pixels[r * m_numCols + c] = val;
    }
}

void Image::setAllPixels(double val)
{
  for( int i = 0; i < m_numRows * m_numCols; ++i )
    {
    m_pixels[i] = val;
    }
}

void Image::operator-=(double val)
{
  for( int i = 0; i < m_numRows * m_numCols; ++i )
    {
    m_pixels[i] -= val;
    }
}

void Image::threshold(double threshold)
{
  for( int r = 0; r < getNumRows(); ++r )
    {
    for( int c = 0; c < getNumCols(); ++c )
      {
          if( std::abs(getPixel(r, c) ) <= threshold )
        {
            setPixel(r, c, 254);
        }
      else
        {
            setPixel(r, c, 0);
        }
      }
    }

}

void Image::maskImage(Image mask, Image image1)
{

  // if images have different sizes, delete old space and allocate new space
  if( m_numRows != mask.m_numRows || m_numCols != mask.m_numCols || m_numRows != image1.m_numRows ||
      m_numCols != image1.m_numCols )
    {
    std::cout << "Images not of same size; cannot mask\n";
    return;
    }
  // now mask pixels
  for( int i = 0; i < m_numRows * m_numCols; ++i )
    {
    if( mask.m_pixels[i] == 0 )
      {
      m_pixels[i] = image1.m_pixels[i];
      }
    }

}

void Image::setAllPixelsWithOldValToNewVal(int oldVal, int newVal)
{
  for( int i = 0; i < m_numRows * m_numCols; ++i )
    {
    if( m_pixels[i] == oldVal )
      {
      m_pixels[i] = newVal;
      }
    }
}


