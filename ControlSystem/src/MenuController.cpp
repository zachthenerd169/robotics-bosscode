#include "../MenuController.h"

bool MenuController::processInput(std::string &processed_input)
{
	return true;
}
//std::string getRequestMenu()
//{
//	//will possibly have more requests later
//	return "1) Get Image & Location\n2) Get Immediate Threats\n3) Return to Robot Control Menu\nEnter a number between 1-3";
//}
std::string getMainMenu()
{
	//need to change enum state
	m_menu_state = main;
	return "1) CONTROL ROBOT\n2) Change Server's IP Address\n3) Change Server's Port Number\n
			4) Send Test Message To Server Without Arduino\n5) Send Test Message To Server With Arduino\n
			6) Quit Program\nEnter a number that is 1-6";
}
std::string getRobotMenu()
{
	//need to change enum state
	m_menu_state = robot_control;
	return "1) request image\n2) request other data\n3) move forward\n4) move backwards\n5) stop\n6) turn right\n7) turn left\n
			8) lower digger\n9) start digging\n10) stop digging\n11) raise digger\n
			choose a number 1-11"; 
}
bool processInput(std::string &processed_input)
{
	if(m_menu_state == main)
	{
		switch(processed_input)
		case 1:
			getRobotMenu();
			return true;
			break;
		case 2:
			//change server IP address
			return true;
			break;
		case 3:
			//change server port number
			return true;
			break;
		case 4:
			//send test message to server sans arduino
			return true;
			break;
		case 5:
			//send test message to server with arduino
			return true;
			break;
		case 6:
			//quit program
			return true;
			break;
		default:
			cout << "inproper input" << endl
			return false;
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
			setinput(forward);
			return true;
			break;
		case 4:
			//move back
			setinput(backwards);
			return true;
			break;
		case 5:
			//stop
			setinput(stop);
			return true;
			break;
		case 6:
			//turn right
			setinput(right);
			return true;
			break;
		case 7:
			//turn left
			setinput(left);
			return true;
			break;
		case 8:
			//lower digger
			setinput(lowerDigger);
			return true;
			break;
		case 9:
			//start digging
			setinput(startDigger);
			return true;
			break;
		case 10:
			//stop digging
			setinput(stopDigger);
			return true;
			break;
		case 11:
			//raise digger
			setinput(raiseDigger);
			return true;
			break;
		default:
			cout << "Improper input" << endl;
			return false;
	}
	else
	{
		cout << "no state" << endl;
	}

}

