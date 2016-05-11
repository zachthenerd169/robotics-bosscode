#include "../UserController.h"
#include <iostream>


void UserController::sendData(std::string data)
{
	std::cout<<"sending data: "<<data<<std::endl;
}
std::string UserController::receiveData()
{
	std:cout<<"received data"<<std::endl;
	std::string test="test";
	return test;
}



