#ifndef ContinuousUpdater_h
#define ContinuousUpdater_h

#include <mutex>
#include <thread>
#include <chrono>

#define DEBUG 1
#if DEBUG
# include <iostream>
# define DEBUG_PRINT(x) std::cout<<x;
#else
# define DEBUG_PRINT(x)
#endif

namespace zwlib
{

/* IUpdater:
 * a simple interface that provides an "update()" method
 */
template<typename TDataType>
class IUpdater {
public:
  virtual TDataType update() = 0;
};

/* ContinuousUpdater:
 * wraps an IUpdater class so that the "update()" function is continuously 
 * called from another thread.  The most recent value is retrieved by 
 * calling "get()".  The updates may be stopped and started at will by calling
 * "stop()" and "start()" respectively.  The recency of the data may also be 
 * checked by calling "ready()" which returns whether the data has been updated
 * since the last call to "get()".
 */
template<typename TDataType>
class ContinuousUpdater {
public:
  // we don't need no stinking default constructor! delete it!
  ContinuousUpdater() = delete;

  // construct a continuous updator using a pointer to an instance of 
  // the class _UpdaterClassPtr and optionally an amount of time to wait after 
  // completion to start the next update.
  ContinuousUpdater(IUpdater<TDataType> *_UpdaterClassPtr, std::chrono::milliseconds _wait_time = std::chrono::milliseconds(0)) :
    my_thread(), // instantiate all of the ContinuousUpdater's members
    UpdaterClassPtr(_UpdaterClassPtr), 
    data(),
    is_old(true),
    mut_data(),
    is_stopped(true),
    mut_stopped(),
    wait_time(_wait_time)
  {}

  // make sure to stop the update cycle when we destroy the ContinuousUpdater
  ~ContinuousUpdater()
  {
    stop();
  }

  // starting is easy!
  void start()
  {
    // grab the mutex assigned to the is_stopped variable
    std::lock_guard<std::mutex> lock(mut_stopped);
    // if we're already started then we don't need to do much
    if(is_stopped)
    {
      // let everyone know that we've started and spawn a new thread to
      // start the update cycle
      DEBUG_PRINT("starting\n");
      is_stopped = false;
      my_thread = std::thread(&ContinuousUpdater::MeUpdate,this);
    }
  }

  // stopping is also easy!
  void stop()
  {
    // grab the mutex assigned to the is_stopped variable
    std::lock_guard<std::mutex> lock(mut_stopped);
    // if we're already stopped then we dont' need to do much
    if(!is_stopped)
    {
      // let everyone know we're stopping and try to join the thread back in
      DEBUG_PRINT("stopping\n");
      is_stopped = true;
      my_thread.join();
      DEBUG_PRINT("stopped\n");
    }
  }

  // tell us whether the data is shiny an new or old and used
  bool ready()
  {
    std::lock_guard<std::mutex> lock(mut_data);
    return !is_old;
  }

  // get the most recent data and let everyone know that we've taken it
  TDataType get()
  {
    std::lock_guard<std::mutex> lock(mut_data);
    is_old = true;
    return data;
  }

private:
  // handle for the thead that gets spawned
  std::thread my_thread;

  // pointer to the IUpdater class we're using
  IUpdater<TDataType>* UpdaterClassPtr;

  // the current data produced by the IUpdater
  TDataType data;

  // whether or not the data has been updated
  bool is_old;

  // mutex to stop data races when reading and setting the data
  std::mutex mut_data;

  // whether or not the update cycle is going or not
  bool is_stopped;

  // mutex to stop data races when stopping and starting the update cycle
  std::mutex mut_stopped;

  // the amount of time to wait after completing an update before starting 
  // the next update
  std::chrono::milliseconds wait_time;

  // wraps the IUpdater's "update()" function in an infinite loop that breaks
  // when is_stopped becomes true
  void MeUpdate()
  {
    while(true)
    {
      std::this_thread::sleep_for(wait_time);
      if(is_stopped)
      {
        DEBUG_PRINT("got stop msg\n");
        break;
      }

      TDataType tmp_data = UpdaterClassPtr->update();

      std::lock_guard<std::mutex> dlock(mut_data);
      DEBUG_PRINT("tick\n");
      is_old = false;
      data = tmp_data;
    }
  }
}; // ContinuousUpdater

} // zwlib

#endif // ContinuousUpdater_h
