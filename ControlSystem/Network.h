/*
 * Network.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 */

#include "lib/PracticalSocket.h"

#ifndef NETWORK_H_
#define NETWORK_H_

class Network
{
	public:

		//Network(){m_socket=new TCPSocket;} need some sort of constructor
		/**
		 * gets the command from the user and sets that command
		 * in the command buffer
		 */
		void receiveCommand();
		/**
		 * gets the data from the data buffer and sends it to the user
		 */
		void sendData();

	private:
		TCPSocket* m_socket;
		CommandBuffer* m_command_buffer;
		DataBuffer* m_data_buffer;
};

#endif /* NETWORK_H_ */
