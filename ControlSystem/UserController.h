/*
 * UserController.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 *
 * Class description: This class is the base class for XboxController or MenuController. UserController will
 * 					  never be instantiated itself b/c it contains an abstract method. UserContoller facilitates
 * 					  sending and receiving data from the robot through a TCPSocket.
 */
#include "lib/PracticalSocket.h" //for TCPSocket

#ifndef USERCONTROLLER_H_
#define USERCONTROLLER_H_

class UserController
{
	public:
		/**
		 * Description: constructor that uses another TCPSocket that already existed outside of this
		 * 				class
		 */
	    UserController(TCPSocket* socket){m_socket=socket;}
	    /**
	     * Description: constructor creates TCPSocket object
	     * Inputs: the IP Address of the NUC (the computer on the robot)
	     * 		   the port number the NUC is listening on
	     */
	    UserController(std::string ip_address, unsigned short port_number){m_socket = new TCPSocket(ip_address, port_number);}
		virtual ~UserController(){} //make virtual to ensure that actual instantiated object is destructed
		/**
		 * Description: receives data from the robot. The type of data the user will
		 * 				receive is sensor data if the Control System is not in debug mode. If the
		 * 				Control System is in debug mode, the user will receive what it sent echoed back
		 * Input:  none
		 * Output: character array of data
		 */
		char* receiveData(void);
		/**
		 * Description: send data to the robot through m_socket. The type of data the user will send are commands or
		 * 				requests.
		 * 				Commands are statements like "move forward"
		 * 				Requests are statements like "get location"
		 * 	Input: a character array of that will either contain a command or request
		 * 	Output: none
		 */
		void sendData(char* data);
		/**
		 * Description: method is to implementd in MenuController & XboxController. it will process the user's
		 *              input whether the input is something like a button press or a command line input
		 * Input: string that will hold the processed input
		 * Output: returns true if processed input successfully, false otherwise
		 */
		virtual bool processInput(std::string &processed_input) = 0;

	private:
		/**
		 * TCP connection between the user and the robot
		 */
		TCPSocket* m_socket;
};



#endif /* USERCONTROLLER_H_ */
