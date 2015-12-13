#include "MarsRobot.h"
#include <stdio.h>

void MarsRobot::startCompetition()
{

  m_period = 0;

  robotInit();

  if(m_period == 0)
  {
    m_period = 1000;
  }

  MainTimer.setPeriod(m_period);
  MainTimer.start();

  while(true)
  {
    if(is_autonomous)
    {
      if(!autonomous_initalized)
      {
        autonomousInit();
        autonomous_initalized = true;
        teleop_initalized = false;
        disabled_initalized = false;
      }
      if(periodReady())
      {
        autonomousPeriodic();
      }
    }
    else if(is_teleop)
    {
      if(!teleop_initalized)
      {
        teleopInit();
        teleop_initalized = true;
        autonomous_initalized = false;
        disabled_initalized = false;
      }
      if(periodReady())
      {
        teleopPeriodic();  
      }
    }
    else if(is_disabled)
    {
      if(!disabled_initalized)
      {
        disabledInit();
        disabled_initalized = true;
        autonomous_initalized = false;
        teleop_initalized = false;
      }
      if(periodReady())
      {
        disabledPeriodic();
      }
    }
    else
    {
      /* No Mode Selected!!! */
      break;
    }
  }
}

void MarsRobot::robotInit()
{
  m_period = 100;
  is_autonomous = true;
  count = 0;
}

bool MarsRobot::periodReady()
{
  if(MainTimer.ready())
  {
    MainTimer.reset();
    return true;
  }
  return false;
}

void MarsRobot::autonomousInit()
{
  printf("Auto Init\n");
  count = 0;
}

void MarsRobot::autonomousPeriodic()
{
  printf("Auto Periodic - %d\n",count);
  ++count;
  if(count >= 8)
  {
    is_autonomous = false;
    is_teleop = true;
  }
}

void MarsRobot::teleopInit()
{
  printf("Teleop Init\n");
  count = 0;
}

void MarsRobot::teleopPeriodic()
{
  printf("Teleop Periodic - %d\n",count);
}

void MarsRobot::disabledInit()
{}

void MarsRobot::disabledPeriodic()
{}

int main(int argc, char const *argv[])
{
  
  MarsRobot robit;

  robit.startCompetition();

  return 0;
}