/*
 * UserController.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 */

#ifndef USERCONTROLLER_H_
#define USERCONTROLLER_H_


class UserController
{
	public:
		virtual ~UserController(){}
		char* receiveData();
		char* sendData(char* data);
		virtual bool processInput() = 0;

	private:
		//TCPSocket m_socket;
};



#endif /* USERCONTROLLER_H_ */
