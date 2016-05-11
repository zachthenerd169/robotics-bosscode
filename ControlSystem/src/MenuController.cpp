#include "../MenuController.h"


std::string MenuController::getMainMenu()
{
	m_menu_state = main;
	std::string menu_text = "1) CONTROL ROBOT\n2) Send Test Message To Server Without Arduino\n3) Send Test Message To Server With Arduino\n\nEnter a number that is 1-3";
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
		int input_switch = stoi(input); //can't switch a string so making it an int
		std::cout<<input_switch<<std::endl;
		switch(input_switch)
		{
			case 1:
				getRobotMenu();
				break;
			case 2:
			{	
				std::string message = obtainAndFormatTestMessage();
				sendData(message);
				break;
			} //need brackets in order to set var message
			case 3:
			{
				std::string message = obtainAndFormatTestMessage();
				sendData(message);
				break;
			}
			default:
				std::cerr << "invalid input\nmust be a single digit 1-3" << std::endl;
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
std::string MenuController::obtainAndFormatTestMessage(bool to_arduino)
{
	std::cout<<"enter message to send: "<<std::endl;
	std:string message;
	getline(std::cin, message);
	return message;
}
bool MenuController::isMainInputValid(std::string input)
{
	if(input.length()>1)
	{
		std::cerr<<"in isValid"<<std::endl;
		std::cerr << "invalid input\nmust be a single digit 1-3" << std::endl;
		return false;
	} 
	else return true;
}

