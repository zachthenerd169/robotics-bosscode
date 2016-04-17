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

#ifndef MENUCONTROLLER_H_
#define MENUCONTROLLER_H_

class MenuController : UserController
{
	public:
		/**
		 * Description: constructor copies TCPSocket, initializes the m_input to null and m_menu_state to main
		 * Inputs: a TCPSocket object
		 */
		MenuController(TCPSocket& socket):UserController(socket), m_input(nullptr), m_menu_state(main){};
		/**
		 * Description: creates a TCPSocket objects, initializes the m_input to null and m_menu_state to main
		 * Inputs: the IP Address of the NUC (the computer on the robot)
	     * 		   the port number the NUC is listening on
		 */
		MenuController(std::string address, unsigned short port):
			UserController(address, port), m_input(nullptr), m_menu_state(main){};
		/**
		 * Description: default constructor
		 * Input: none
		 */
		MenuController():UserController(), m_input(nullptr), m_menu_state(nullptr){};
		/**
		 * Description: setters for class attributes
		 * Input: menu state or user input
		 */
		void setInput(std::string input){m_input=input;}
		void setMenuState(std::string menu_state){m_menu_state=menu_state;}
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
		/**
		 * Description: displays the robot control menu
		 * 				<<I don't know what the commands will be yet>>
		 * 				2) Display request menu
		 * Inputs: none
		 * Outputs: string that holds the robot control menu
		 */
		std::string getRobotMenu();
		/**
		 * Description: displays the request data menu
		 * 			    1) Get Image & Location
		 * 			    2) Get Immediate Threats
		 * 			    3) Return to Robot Control Menu
		 * 			    <<I'm not really sure what all of the requests will be yet>>
		 *  Inputs: none
		 *  Outputs: string that holds the request control menu
		 */
		std::string getRequestMenu();
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
		 * 			2) there wasn't a user input to interpret
		 */
		bool processInput(std::string &processed_input);

	private:

		/**
		 * user's command-line input
		 */
		std::string m_input;
		/**
		 * hold's the state of the menu display, i.e., if the user is looking at the
		 * main menu m_menu_state==main
		 */
		enum MenuState {main, robot_control, request} m_menu_state;

};
#endif /* MENUCONTROLLER_H_*/
