/*
 * XboxController.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 * Class Desciption:
 * Control Key:
 */

#ifndef XBOXCONTROLLER_H_
#define XBOXCONTROLLER_H_

class XboxController : UserController
{
	public:
		/**
		 * Description: constructor copies TCPSocket, xbox controller is initialized so the nothing is pressed
		 * Inputs: a TCPSocket object
		 */
		XboxController(TCPSocket& socket):UserController(socket),m_xbox_controller({0,0,0,0,0,0,0,0,0,0,0,0}){};
		/**
		 * Description: creates a TCPSocket objects, xbox controller is initialized so the nothing is pressed
		 * Inputs: the IP Address of the NUC (the computer on the robot)
		 * 		   the port number the NUC is listening on
		 */
		XboxController(std::string address, unsigned short port):
				UserController(address, port),m_xbox_controller({0,0,0,0,0,0,0,0,0,0,0,0}){};
		/**
		 * Description: <<how will this method work?>>
		 * Inputs: string that stores the processed input that is to be sent to the robot
		 * Outputs: returns true if command was successfully processed, returns false
		 * 			otherwise.
		 */
		bool processInput(std::string &processed_input);
	private:
		/**
		 * holds the state of the xbox controller
		 * if a member value is false it is not pressed
		 * if a member value is true it is pressed
		 */
		struct ControllerState
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

};
#endif /* XBOXCONTROLLER_H_ */
