#include "../UserController.h"
#include <iostream>
//#include <stdio.h>
//#include <string.h>


bool UserController::sendData(std::string data)
{
	std::cout<<"sending: "<<data<<std::endl;
    try
    {
        const char* packet=data.c_str();
        m_socket -> send(packet, strlen(packet)); //send message to server
        return true;
    }
    catch(SocketException &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

}
std::string UserController::receiveData()
{
	std:cout<<"received data"<<std::endl;
	std::string test="test";
	return test;
}



