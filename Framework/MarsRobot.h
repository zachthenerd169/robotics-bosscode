
#include <set>
#include "Timer.h"

class MarsRobot
{
public:
	void robotInit();
  void startCompetition();
  void autonomousInit();
  void autonomousPeriodic();
  void teleopInit();
  void teleopPeriodic();
  void disabledInit();
  void disabledPeriodic();
private:
  unsigned int m_period;
  bool periodReady();
  bool is_autonomous;
  bool is_teleop;
  bool is_disabled;
  bool autonomous_initalized;
  bool teleop_initalized;
  bool disabled_initalized;

  unsigned int count;
  Timer MainTimer;
};