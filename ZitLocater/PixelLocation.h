/**
* @file
* @author Hans J. Johnson
* @brief The PixelLocation class file 
*/

#ifndef PixelLocation_H_
#define PixelLocation_H_


/**
 * @brief A Class to represent a pixel location.
 */
class PixelLocation
{
public:
  /**
   * @brief Constructor with default values of 0 for row and col
   *
   */
  PixelLocation(): m_row(0), m_col(0) {}
  /**
   * @brief Constructor with initial values
   *
   * @param row The row location
   * @param col The col location
   */
  PixelLocation(const int row, const int col): m_row(row), m_col(col) {}
  /**
   * @brief Get the row value
   *
   * @return The row value
   */
  int GetRow() const { return m_row; }
  /**
   * @brief Get the column value
   *
   * @return the column value
   */
  int GetCol() const { return m_col; }
  /**
   * @brief Set the row value
   *
   * @param row The new row value
   */
  void SetRow(const int row) { m_row = row; }
  /**
   * @brief Set the column value
   *
   * @param col The new column value
   */
  void SetCol(const int col) { m_col = col; }
    

private:
  int m_row;
  int m_col;
};

#endif //PixelLocation_H_
