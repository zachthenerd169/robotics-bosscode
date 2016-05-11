/*
 * MenuController.h

 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 * Class description: MenuController allows the user to control the robot through a
 * 					  command line interface. The user will select options 3 different types
 * 					  of menus:
 * 					  1) The main menu (for changing client-side info or testing client-server
 * 					  	 code)
 * 					  2) The robot control menu (will be used when we acutally want to control
 * 					  	 the robot)
 * 					  3) The request data menu (will only be accessable from the robot control
 * 					     robot)
 * 					  MenuController will receive the user input and send out a command to
 * 					  the robot. The logic to decide what command will be sent out is defined in
 * 					  processInput.
 */

#include "UserController.h"
#ifndef MENUCONTROLLER_H_
#define MENUCONTROLLER_H_

class MenuController : public UserController
{
	public:
		/**
		 * Description: creates a TCPSocket objects, initializes the m_input to null and m_menu_state to main
		 * Inputs: the IP Address of the NUC (the computer on the robot)
	     * 		   the port number the NUC is listening on
		 */
		MenuController(std::string address, unsigned short port):
			UserController(address, port), m_menu_state(main){};
		/**
		 * Description: displays the main menu
		 * 				1) Control Robot
		 * 				2) Send Test Message To Robot
		 * 				3) Display IP/Port
		 * 				4) Change IP/Port
		 * 				5) Quit Program
		 * Inputs: none
		 * Outputs: string that holds the main menu
		 */
		std::string getMainMenu();
		//DESTRUCCTTTIOOOON!!!
		 ~MenuController(){}
		/**
		 * Description: displays the robot control menu
		 * 				<<I don't know what the commands will be yet>>
		 * 				2) Display request menu
		 * Inputs: none
		 * Outputs: string that holds the robot control menu
		 */
		std::string getRobotMenu();
		/**
		 * Description: method looks at m_menu_state & m_input and decides what command
		 * 				to send to the robot
		 * Inputs: string that stores the command to be sent to the robot
		 * Outputs: returns true if command was successfully processed, returns false
		 * 			otherwise.
		 * 			Reasons a command was not successfully processed would be:
		 * 			1) user did not input the command correctly (m_user_input does not
		 * 			   match any of the acceptable command formats). in this case an
		 * 			   error message will be displayed.		
		 */
		 bool processInput();
		 
	private:
		/**
		 * hold's the state of the menu display, i.e., if the user is looking at the
		 * main menu m_menu_state==main
		 */
		enum MenuState {main, robot_control, request} m_menu_state;

		//private helper functions
		bool isValidAddress(std::string address);
		void obtainAndSetAddress();
		void obtainAndSetPort();
		std::string obtainAndFormatTestMessage(bool to_arduino=false);
		bool isValidPort(unsigned short);
		bool isMainInputValid(std::string input);

};
#endif /* MENUCONTROLLER_H_*/


