/* Compile with: g++ -Wall -std=c++11 -o ThreaddedNetworkTest.exe ThreadingTest.cpp  ThreaddedNetwork.cpp PracticalSocket.cpp -lpthread
*/

#include "ThreaddedNetwork.h"

int main(int argc, char *argv[])
{
  if (argc != 2) //Test for correct number of arguments
  {
    cerr << "Usage: " << argv[0] << " <Server Port>" << endl;
    exit(1);
  }
  unsigned short servPort = atoi(argv[1]); //First arg: local port

  /* Make the Threaded Network */
  ThreaddedNetwork network(servPort);

  while(true)
  {
    /* get any new messages from the network */
    std::vector<std::string> data = network.getNewMessages(); 
    if(!data.empty())
    {
      std::cout << "Received new data:\n";
      for(int i=0; i<data.size(); i++)
      {
        std::cout << data.at(i) << "\n";
      }
      std::cout <<"End new data\n";
    }
  }

  return 0;
}




