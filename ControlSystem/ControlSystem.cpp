//============================================================================
// Name        : ControlSystem.cpp
// Description : Main Robot Code
// Compiling   : g++ -Wall -std=c++11 -o ControlSystem.exe ControlSystem.cpp src/ThreaddedNetwork.cpp lib/PracticalSocket.cpp -lpthread

//============================================================================
#include <iostream>
#include "ThreaddedNetwork.h"
#include <vector>

int main(int argc, char *argv[])
{
  /* Read Command Line Arguments */
  /* Correct Usage: ./ControlSystem.exe 12345 */
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <Server Port>" << endl;
    exit(1);
  }
  unsigned short server_port = atoi(argv[1]);


  /* Display welcome message */
  std::cout << std::endl
            << "University of Iowa Robotics Club Presents:" << std::endl
            << "2016 NASA Robotic Mining Competition Robot" << std::endl
            << "------------------------------------------" << std::endl
            << std::endl;

  /* Construct robot components */
  ManualProcessor.h


  /* Main program loop */
  while(true)
  {
    /* check for any new messages from the server */
    if( network.hasNewMessages() )
    {
      /* Processes incoming messages */
      auto newMessages = network.getNewMessages();
      for(unsigned int i=0; i<newMessages.size(); i++)
      {
        /* for now just print the messages */
        std::cout << newMessages.at(i) << std::endl;

        /* pseudo-code */
        switch(newMessages.at(i)[0])
        {
          case 'M': // movement command
            
            break;
          case 'S': // sensor request
            break;
          case 'I': // image request
            break;
          case 'T': // test message
            break;
          default:  // unknown message
            break;
        }
      }
    }

    /* Update robot state */
    //

    /* Send back data */
    //
  }
  return 0;
}
