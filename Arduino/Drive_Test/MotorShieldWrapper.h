//#include "DualVNH5019MotorShield.h"

class MotorShieldWrapper
{
public:
  MotorShieldWrapper()
  {
    m_one = 0;
    m_two = 0;
  }

  void begin()
  {
    m_md.init()
  }

  void setMotorOne(int power)
  {
    m_one = power;
    m_md.setSpeeds(power,m_two);
  }

  void setMotorTwo(int power)
  {
    m_two = power;
    m_md.setSpeeds(m_one,power);
  }
  
private:
  DualVNH5019MotorShield m_md;

  int m_one;
  int m_two;
};
