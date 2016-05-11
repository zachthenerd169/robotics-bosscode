#include "../MenuController.h"
#include <regex> //for error checking


//std::string getRequestMenu()
//{
//	//will possibly have more requests later
//	return "1) Get Image & Location\n2) Get Immediate Threats\n3) Return to Robot Control Menu\nEnter a number between 1-3";
//}
std::string MenuController::getMainMenu()
{
	m_menu_state = main;
	return "1) CONTROL ROBOT\n2) Change Server's IP Address\n3) Change Server's Port Number\n
			4) Send Test Message To Server Without Arduino\n5) Send Test Message To Server With Arduino\n
			\nEnter a number that is 1-5";
}
std::string MenuController::getRobotMenu()
{
	m_menu_state = robot_control;

	// return "1) request image\n2) request other data\n3) move forward\n4) move backwards\n5) stop\n6) turn right\n7) turn left\n
	// 		8) lower digger\n9) raise digger\n
	// 		choose a number 1-9";

	return "\nMODE KEY: DESIRED ACTION <user input>\nSTOP ROBOT: <1>\n"+
	"MOVE STRAIGHT FORWARD: <2 powerLevel>\nMOVE STRAIGHT REVERSE: <3 powerLevel>\n"+
	"TURN RIGHT: <4 powerLevel>\nTURN LEFT: <5 powerLevel>\nDIGGER DROP: <6>\nRAISE DIGGER:"+ 
	"<7>\nDUMP BUCKET: <8>\nLOWER BUCKET: <9>\nREQUEST SENSOR DATA <10>"+
	"REQUEST IMAGE: <spacebar>\n\nPRINT KEY <help>";

}
bool MenuController::processInput(std::string &processed_input)
{
	if(m_menu_state == main)
	{
		switch(processed_input)
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
			std::string message = obtainAndFormatTestMessage()
			sendData(message);
			break;
		case 5:
			std::string message = obtainAndFormatTestMessage()
			sendData(message);
			break;
		default:
			std::cout << "improper input" << std::endl
			return false; //did not successfully process input
			break;

		return true; //successfully processed input	
	} 
	else if (m_menu_state == robot_control) 
	{
		switch(processed_input)
		case 1:
			//request image
			return true;
			break;
		case 2:
			//request other data
			return true;
			break;
		case 3:
			//move forward
			setinput("2 " + defaultPowerLevel);
			return true;
			break;
		case 4:
			//move back
			setinput("3 " + defaultPowerLevel);
			return true;
			break;
		case 5:
			//stop
			setinput("1");
			return true;
			break;
		case 6:
			//turn right
			setinput("4 " + defaultPowerLevel);
			return true;
			break;
		case 7:
			//turn left
			setinput("5 " + defaultPowerLevel);
			return true;
			break;
		case 8:
			//lower digger, automatically starts digging
			setinput("6");
			return true;
			break;
		case 9:
			//raise digger, automatically stops digging
			setinput("7");
			return true;
			break;
		default:
			cout << "Improper input" << endl;
			return false;
	}
	else
	{
		cout << "no state" << endl;
		return false;
	}
}
void obtainAndSetPort()
{
	std::cout<<"current port is: "<<m_socket->GetLocalPort()<<
	"\nenter new port: "<<std::endl;
	std::string new_port;
	std::cin.ignore();
	getline(std::cin,new_port);
	if(isValidAddress(new_port) m_socket -> SetLocalAddress(new_address)
	else std::cout<<"did not set address b/c address was invalid"<<std::endl;
}
void MenuController::obtainAndSetAddress()
{
	std::cout<<"current address is: "<<m_socket->GetLocalAddress()<<
	"\nenter new address: "<<std::endl;
	std::string new_address;
	std::cin.ignore();
	getline(std::cin,new_address);
	if(isValidAddress(new_address)) m_socket -> SetLocalAddress(new_address)
	else std::cout<<"did not set address b/c address was invalid"<<std::endl;
}				
bool MenuController::isValidAddress(std::string address)
{
	return true;
}
bool MenuController::isValidPort(unsigned short)
{
	return true;
}
std::string MenuControlller::obtainAndFormatTestMessage(to_arduino)
{
	std::cout<<"enter message to send: "<<std::endl;
	std:string message;
	std::cin.ignore();
	getline(std::cin, message);
}
std::string getUserInput()
{

}

