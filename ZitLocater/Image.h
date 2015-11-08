/**
* @file
*
* @author Mona K. Garvin (Revised by Hans J. Johnson)
*
* @brief Header file for Image class for homework 5.
*
* This class represents a grayscale image that can be read from a bmp file
* and written to a bmp file in two ways (grayscale mapping and
* randomized color mapping)
*/

#ifndef IMAGE_H
#define IMAGE_H

#include <string>

/**
* @brief A C++ class to represent images in memory.
*/
class Image
{
public:
  // --------------------------------------
  // GROUP: Construction/destruction/copy
  // --------------------------------------
  /**
   * @brief Default constructor with no image rows or columns.
   *
   *  Subsequent calls to readFromBMPFile may fill the image in later.
   *
   */
  Image();

  /**
   * @brief Constructor to specify size
   *
   * @param numRows The number of image rows
   * @param numCols The number of image columns
   */
  Image(int numRows, int numCols);

  /**
   * @brief Copy constructor
   *
   * @param imageToCopyFrom
   */
  Image(const Image & imageToCopyFrom);

  /**
   * @brief Destructor
   *
   */
  ~Image();

  /**
   * @brief  assignment operator
   *
   * @param imageOnRight
   *
   * @return
   */
  const Image & operator=(const Image & imageOnRight);

  /**
   * @brief Add Assignment operator
   *
   * @param imageOnRight
   *
   * @return
   */
  const Image & operator+=(const Image & imageOnRight);

  /**
   * @brief Multiply Assignment operator
   *
   * @param imageOnRight
   *
   * @return 
   */
  const Image & operator*=(const Image & imageOnRight);


  // -----------------------------------
  // GROUP: Image input (from file)
  // -----------------------------------
  /**
   * @brief create image from file
   *
   * Given filenmame of .bmp file the image is converted to grayscale
   *
   * @param inputFileName
   *
   * @return
   */
  bool readFromBMPFile(const std::string & inputFileName);

  // -----------------------------------
  // GROUP: Image output (to file)
  // -----------------------------------
  /**
   * @brief Write image to file.
   *
   * Given .bmp filename the mapping between intensity values and color
   * values will be based on the current color mapping
   * (see switchToGrayColorMapping() and switchToRandomColorMapping() functions)
   *
   * @param outputFileName
   *
   * @return
   */
  bool writeToBMPFile(const std::string & outputFileName);

  // -----------------------------
  // GROUP: Data accessors
  // -----------------------------

  /**
   * @brief get pixel value, given input row and column
   *
   * @param r Row of pixel to get value
   * @param c Column of pixel to get value
   *
   * @return Pixel value at (r,c) location
   */
  double getPixel(int r, int c) const;

  /**
   * @brief determine whether given pixel location (row/column) is in bounds
   *
   * @param r Row of location to check
   * @param c Column of location to check
   *
   * @return true if (r,c) are valid image locations
   */
  bool isInBounds(int r, int c) const;

  /**
   * @brief get number of rows
   *
   * @return The number of rows in the image
   */
  int getNumRows() const;

  /**
   * @brief get number of columns
   *
   * @return The number of columns in the image
   */
  int getNumCols() const;

  // -----------------------------
  // GROUP: Data modification
  // -----------------------------

  /**
   * @brief set pixel value at row r and column c to val
   *
   * @param r Row location
   * @param c Column location
   * @param val The value to set at (r,c) location
   */
  void setPixel(int r, int c, double val);

  /**
   * @brief set all pixel values to val
   *
   * @param val The value to set all pixels to
   */
  void setAllPixels(double val);

  /**
   * @brief Subtract a constant value from every pixel location
   *
   * @param val The value to subtract
   */
  void operator-=(double val);

  /**
   * @brief
   *
   * @param threshold
   */
  void threshold(double threshold);

  /**
   * @brief If the image value is greater than zero, set to zero, else set to 1
   */
  void logicalNot();

  /**
   * @brief
   *
   * @param oldVal
   * @param newVal
   */
  void setAllPixelsWithOldValToNewVal(int oldVal, int newVal);

  /**
   * @brief
   *
   * @param mask
   * @param image1
   */
  void maskImage(Image mask, Image image1);

public:
  int      m_numRows; /*!< number of rows */
  int      m_numCols; /*!< number of columns */
  double * m_pixels;  /*!< pointer to first pixel in image */
};

#endif // IMAGE_H
