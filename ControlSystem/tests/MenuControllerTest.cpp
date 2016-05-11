#include "../lib/PracticalSocket.h"
#include "../MenuController.h"

#include <iostream>
#include <string.h>
#include <memory>

// To compile: g++ -std=c++11 -o menutest.exe tests/MenuControllerTest.cpp src/UserController.cpp lib/PracticalSocket.cpp
int main (void)
{
	std::string address;
	unsigned short port;
	
	std::cout<<"Enter IP address of the server: "<<std::endl;
	std::cin.ignore();
	getline(std::cin, address);
	std::cout<<"Enter the port the server is listening on"<<std::endl;
	std::cin>>port;

    MenuController menu(address, port); //construct menu object
  	std::cout<<menu.getMainMenu();
    while(true)
    {
    	std::string user_input;
    	std::cin.ignore();
		getline(std::cin, user_input);
		menu.setInput(user_input);
		bool success=menu.processInput();
		if(!success)std::cout<<"didn't process input correctly"<<std::endl;
    }

	
    return 0;
}

