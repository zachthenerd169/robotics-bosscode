#include "../MenuController.h"


std::string MenuController::getMainMenu()
{
	m_menu_state = main;
	std::string menu_text = "1) CONTROL ROBOT\n2) Change Server's IP Address\n3) Change Server's Port Number\n4) Send Test Message To Server Without Arduino\n5) Send Test Message To Server With Arduino\n\nEnter a number that is 1-5";
	return menu_text;
}
std::string MenuController::getRobotMenu()
{
	m_menu_state = robot_control;
	return "\nMODE KEY: DESIRED ACTION <user input>\nSTOP ROBOT: <1>\nMOVE STRAIGHT FORWARD: <2 powerLevel>\nMOVE STRAIGHT REVERSE: <3 powerLevel>\nTURN RIGHT: <4 powerLevel>\nTURN LEFT: <5 powerLevel>\nDIGGER DROP: <6>\nRAISE DIGGER:<7>\nDUMP BUCKET: <8>\nLOWER BUCKET: <9>\nREQUEST SENSOR DATA <10>\nREQUEST IMAGE: <spacebar>\n\nPRINT KEY <help>";
}
bool MenuController::processInput()
{
	std::string input=getInput(); //getting the input that was set in the main loop
	if(!isMainInputValid(input)) return false; //if the input is the incorrect level don't proccess it
	if(m_menu_state == main) //if we are procesing an input to the main menu
	{
		char input_switch = input.at(0); //can't switch a string so make it a char
		switch(input_switch)
		{
			case 1:
				getRobotMenu();
				break;
			case 2:
				obtainAndSetAddress();
				break;
			case 3:
				obtainAndSetPort();
				break;
			case 4:
			{
				std::string message = obtainAndFormatTestMessage();
				sendData(message);
				break;
			} //need brackets in order to set var message
			case 5:
			{
				std::string message = obtainAndFormatTestMessage();
				sendData(message);
				break;
			}
			default:
				std::cerr << "invalid input\nmust be a single digit 1-5" << std::endl;
				return false; //did not successfully process input
				break;
		}	
		return true; //successfully processed input	
	} 
	else if (m_menu_state == robot_control) 
	{
		return true;
	}
	else
	{
		std::cerr << "FUCK SOMETHING WENT WRONG IN MENUCONTROLLER" << std::cerr;
		return false;
	}
}
void MenuController::obtainAndSetPort()
{
	// std::cout<<"current port is: "<< getSocket()->GetLocalPort()<<
	// "\nenter new port: "<<std::endl;
	// std::string new_port;
	// std::cin.ignore();
	// getline(std::cin,new_port);
	// if(isValidAddress(new_port) getSocket() -> SetLocalAddress(new_address)
	// else std::cout<<"did not set address b/c address was invalid"<<std::endl;
}
void MenuController::obtainAndSetAddress()
{
	// std::cout<<"current address is: " << getSocket()->GetLocalAddress()<<
	// "\nenter new address: "<<std::endl;
	// std::string new_address;
	// std::cin.ignore();
	// getline(std::cin,new_address);
	// if(isValidAddress(new_address)) getSocket() -> SetLocalAddress(new_address)
	// else std::cout<<"did not set address b/c address was invalid"<<std::endl;
}				
bool MenuController::isValidAddress(std::string address)
{
	return true;
}
bool MenuController::isValidPort(unsigned short)
{
	return true;
}
std::string MenuController::obtainAndFormatTestMessage(bool to_arduino)
{
	std::cout<<"enter message to send: "<<std::endl;
	std:string message;
	std::cin.ignore();
	getline(std::cin, message);
	return message;
}
bool MenuController::isMainInputValid(std::string input)
{
	if(input.length()>1)
	{
		std::cerr << "invalid input\nmust be a single digit 1-5" << std::endl;
		return false;
	} 
	else return true;
}

