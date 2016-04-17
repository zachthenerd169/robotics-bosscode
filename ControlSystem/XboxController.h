/*
 * XboxController.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 * Class Description: XboxController allows the user to control the robot with and xbox controller,
 * 					  If using an xbox controller, the client code must be loaded on a windows computer
 *
 * Control Key:
 */

#include "CXBOXController.h"

#ifndef XBOXCONTROLLER_H_
#define XBOXCONTROLLER_H_

class XboxController : UserController
{
	public:
		/**
		 * Description: constructor copies TCPSocket, xbox controller is initialized so the nothing is pressed
		 * Inputs: a TCPSocket object
		 */
		XboxController(TCPSocket& socket):UserController(socket),m_xbox_controller({1,1,1,1,1,1,1,1,1,1,1,1}){};
		/**
		 * Description: creates a TCPSocket objects, xbox controller is initialized so the nothing is pressed
		 * Inputs: the IP Address of the NUC (the computer on the robot)
		 * 		   the port number the NUC is listening on
		 */
		XboxController(std::string address, unsigned short port):
				UserController(address, port),m_xbox_controller({1,1,1,1,1,1,1,1,1,1,1,1}){};
		/**
		 * Description: default constructor
		 * Input: none
		 */
		XboxController():UserController(),m_xbox_controller({1,1,1,1,1,1,1,1,1,1,1,1}){};
		/**
		 * Description: <<how will this method work?>>
		 * Inputs: string that stores the processed input that is to be sent to the robot
		 * Outputs: returns true if command was successfully processed, returns false
		 * 			otherwise.
		 */
		bool processInput(std::string &processed_input);
		/**
		 * Description: setters for class attributes
		 * Input: menu state or user input
		 */
		void setPowerLevel(std::string powerLevel){m_power_level=powerLevel;}

		/**
		* constant that specifies the absolute largest power level
		*/
		static const int MAX_POWER_LEVEL = 50;
	private:
		/**
		 * holds the button press state of the xbox controller
		 * if a member value is false the button is being held
		 * if a member value is true the button is released
		 */
		struct ButtonState
		{
			bool endA;
			bool endB;
			bool endX;
			bool endY;
			bool endUp;
			bool endDown;
			bool endStart;
			bool endRB;
			bool endLB;
			bool endRThumb;
			bool endLThumb;
		}m_xbox_controller;

		/**
		* holds the current power level as adjusted
		* by the controller
		*/
		int m_power_level;

		/**
		* holds the current state of the xbox controller
		*/
		XINPUT_STATE m_state;

		/**
		* points to the controller being used
		*/
		CXBOXController* m_player_controller;

};
#endif /* XBOXCONTROLLER_H_ */
