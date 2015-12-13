#ifndef Timer_h
#define Timer_h

#include <chrono>

class Timer
{
public:
  typedef std::chrono::duration<int,std::milli> Tduration;
  typedef std::chrono::steady_clock             Tclock;
  typedef Tclock::time_point Ttime_point;

  Timer()
  {
    m_period = Tduration(0);
    m_enabled = false;
  }

  void setPeriod(unsigned int period)
  {
    m_period = Tduration(period);
  }

  bool ready()
  {
    if(m_enabled)
    {
      return std::chrono::duration_cast<Tduration>(Tclock::now() - m_start_time) >= m_period;
    }
    return false;
  }

  void start()
  {
    m_enabled = true;
    m_start_time = Tclock::now();
  }

  void stop()
  {
    m_enabled = false;
  }

  void reset()
  {
    m_start_time = Tclock::now();
  }

private:
  bool m_enabled;
  Tduration m_period;
  Ttime_point m_start_time;
};

#endif // Timer_h

