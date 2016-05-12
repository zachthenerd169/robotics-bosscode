#include "../UserController.h"
#include <iostream>


bool UserController::sendData(std::string data)
{
	std::cout<<"sending: "<<data<<std::endl;
    try
    {

        m_socket -> send(data.c_str(), strlen(data.c_str())); //send message to server
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



