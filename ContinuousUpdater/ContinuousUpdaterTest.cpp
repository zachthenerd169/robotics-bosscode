#include <iostream>
#include <chrono>

#include "ContinuousUpdater.h"

/* Thing:
 * Very simple implementation of IUpdater that just increments an internal
 * counter everytime "update()" is called.  A delay is added to simulate
 * "update()" being an expensive operation.
 */
class Thing : public zwlib::IUpdater<int>
{
public:
  Thing()
  {
    count = 0;
  }

  int update()
  {
    ++count;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return count;
  }
private:
  int count;
};

int main(int argc, char const *argv[])
{
  // make a thing
  Thing th1;

  // make a continuous updater to continuosly update the thing
  zwlib::ContinuousUpdater<int> cu(&th1);

  // start the continuous updater
  cu.start();

  // look Ma! no blocking!
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "it's " << cu.get() << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));

  // stop the continuous updater
  cu.stop();

  // show the final value of the continuous updater
  std::cout << "now it's " << cu.get() << std::endl;

  return 0;
}