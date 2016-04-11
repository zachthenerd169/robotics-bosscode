/*
 * UserController.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 *
 * Class description:
 */
#include "lib/PracticalSocket.h"

#ifndef USERCONTROLLER_H_
#define USERCONTROLLER_H_

class UserController
{
	public:
		/**
		 * Constructor that uses another TCPSocket that already existed outside of this
		 * class
		 */
	    UserController(TCPSocket* socket){m_socket=socket;}
	    UserController(std::string ip_address, unsigned short port_number);
		virtual ~UserController(){}
		/**
		 * Description: receives data from the robot. The type of data the user will
		 * 				receive is sensor data.
		 * Parameters:  none
		 * Returns:     character array of data
		 * Implemented by:
		 */
		char* receiveData(void);
		char* sendData(char* data);
		virtual bool processInput(void) = 0;

	private:
		TCPSocket* m_socket;
};



#endif /* USERCONTROLLER_H_ */
