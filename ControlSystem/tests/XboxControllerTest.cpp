#include "../lib/PracticalSocket.h"
#include "../XboxController.h"

#include <iostream>
#include <string.h>
#include <memory>
#define DEBUG 1

// To compile: g++ --std=c++11 -o xboxtest.exe tests/XboxControllerTest.cpp src/UserController.cpp src/XboxController.cpp lib/PracticalSocket.cpp lib/CXboxController.cpp
int main (int argc, char** argv)
{
	std::string address;
	unsigned short port;
#if DEBUG
	port=1024;
	address="127.0.0.1";
#else
	if(argc != 3)
	{
 	  	cerr << "Usage: " << argv[0] << " <Server Address> <Server Port>" << endl;
    	exit(1);
    }
    else
    {
    	address=argv[1];
    	try{ port=atoi(argv[2]);}
    	catch(...){
    		std::cerr<<"invalid port number"<<std::endl;
    		exit(1);
    	}
    }
#endif
	XboxController xboxcontroller(address, port); //construct xbox controller object
	//XboxController xboxcontroller; //This is used for testing without networking code

    while(true)
    {
		std::cout<<"\n\n"<<xboxcontroller.getMenu()<<std::endl;
		bool success=xboxcontroller.processInput(); //not really doing anything with success right now
		if(success)
		{
			// send the data to the server
			xboxcontroller.sendData(xboxcontroller.getInput());
			//std::cout << xboxcontroller.getInput(); // This is used for testing the buttons
		}
		else
		{
			// Exited for some reason or another
			return 0;
		}
	}
    return 0;
}



