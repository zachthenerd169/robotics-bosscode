#include "../lib/PracticalSocket.h"
#include "../MenuController.h"

#include <iostream>
#include <string.h>
#include <memory>
#define DEBUG 1

// To compile: g++ --std=c++11 -o menutest.exe tests/MenuControllerTest.cpp src/UserController.cpp src/MenuController.cpp lib/PracticalSocket.cpp
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
	MenuController menu(address, port); //construct menu object
 	std::cout<<"\n\n"<<menu.getMainMenu()<<std::endl;
  	
    while(true)
    {
        std::string server_data;
        std::string user_input;
		getline(std::cin, user_input);
		menu.setInput(user_input);
		bool success=menu.processInput(); //not really doing anything with success right now
		if(menu.inMainMenu()){std::cout<<"\n\n"<<menu.getMainMenu()<<std::endl;}
        // server_data=menu.receiveData(); //try to get messages back from the server
        // if(server_data.length()>=1){
        //     std:cout<<"Server: "<<server_data<<std::endl;
        // }


	}
    return 0;
}



