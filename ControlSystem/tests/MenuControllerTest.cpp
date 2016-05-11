#include "../lib/PracticalSocket.h"
#include "../MenuController.h"

#include <iostream>
#include <string.h>
#include <memory>
#define DEBUG 1

// To compile: g++ -std=c++11 -o menutest.exe tests/MenuControllerTest.cpp src/UserController.cpp lib/PracticalSocket.cpp
int main (void)
{
	std::string address;
	unsigned short port;
#if DEBUG	
	port=1024;
	address="127.0.0.1";  
#else 
 	std::cout<<"Enter IP address of the server: "<<std::endl;
	getline(std::cin, address);
	std::cout<<"Enter the port the server is listening on"<<std::endl;
	std::cin>>port;
#endif	
	MenuController menu(address, port); //construct menu object
 	std::cout<<"\n\n"<<menu.getMainMenu()<<std::endl;
  	
    while(true)
    {
    	std::string user_input;
		getline(std::cin, user_input);
		menu.setInput(user_input);
		bool success=menu.processInput();
		if(menu.inMainMenu()){std::cout<<"\n\n"<<menu.getMainMenu()<<std::endl;}
		//if(!success)std::cout<<"didn't process input correctly"<<std::endl;
    }

	
    return 0;
}

