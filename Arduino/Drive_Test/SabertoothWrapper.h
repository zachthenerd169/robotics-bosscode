//#include "Sabertooth/Sabertooth.h"
//#include <Sabertooth.h>

class SaberWrapper
{
public:
  SaberWrapper(int pin) :
    m_sw_serial(NOT_A_PIN,pin),
    m_sabertooth(m_sw_serial)
  {
  }

  void begin()
  {
    m_sw_serial.begin(9600);
    m_sabertooth.autobaud();
    m_sabertooth.setRamping(55);
  }

  void setMotorOne(int power)
  {
    m_sabertooth.motor(1,power);
  }

  void setMotorTwo(int power)
  {
    m_sabertooth.motor(2,power);
  }
  
private:
  SoftwareSerial m_sw_serial;
  Sabertooth m_sabertooth;
};

