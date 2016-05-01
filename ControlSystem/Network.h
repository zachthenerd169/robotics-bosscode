/*
 * Network.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 * Class Description: Network receives requests and commands from the UserController.
 * 				      Network if is in DEBUG mode if will automatically echo the messages
 * 				      back to the user. If there is any data in the m_out_buffer then
 * 				      Network will send that data back to the user.
 */

#include "CommandBuffer.h"
#include "DataBuffer.h"
#include "lib/PracticalSocket.h" //for m_socket
#include <memory> //for smart pointer

#ifndef NETWORK_H_
#define NETWORK_H_

class Network
{
	public:
		/**
		 * Description: constructs and new TCPSocket from info provided by the user &
		 * 				and creates a new reference to the data buffer & command buffer
		 * Inputs: the IP Address of the NUC (the computer on the robot)
	     * 		   the port number the NUC is listening on
	     * 		   a CommandBuffer object
	     * 		   a DataBuffer object
		 */
		Network(std::string address, unsigned short port, const CommandBuffer& in_buffer, const DataBuffer& out_buffer):
				m_socket(new TCPServerSocket(address, port)), m_in_buffer(in_buffer), m_out_buffer(out_buffer){}
		/**
		 * Description: creates a new reference to a TCPSocket, DataBuffer & CommandBuffer
		 * Inputs: TCPSocket object, CommandBuffer object, & DataBuffer & CommandBuffer
		 */
		Network(const TCPSocket& socket, const CommandBuffer& in_buffer, const DataBuffer& out_buffer):
			m_socket(socket), m_in_buffer(in_buffer), m_out_buffer(out_buffer){}
		/**
		 * Description: default constructor
		 * Inputs: none
		 */
		Network():m_socket(nullptr),m_in_buffer(nullptr),m_out_buffer(nullptr){}
		/**
		 * Description: setters for all of the the objects. This will typically
		 * 				be used if the default constructor is chosen
		 * 	Inputs: the objec we want to be set
		 */
		// void setSocket(TCPSocket& socket){m_socket=socket;}
		// void setInBuffer(CommandBuffer& in_buffer){m_in_buffer=in_buffer;}
		// void setOutBuffer(DataBuffer& out_buffer){m_out_buffer=out_buffer;}
		/**
		 * Decription: receives data from the user through the TCPSocket. after the data
		 * 			   is received, it will add the data to the in_buffer
		 *  Inputs: none
		 *  Outputs: none
		 */
		void receiveData();
		/**
		 * Description: sends data back to the user.
		 *  			this data could either be sensor data could either be sensor
		 *  			data or debugging information. If there is any data in the data buffer
		 *  			it will automatically send it back to the user.
		 *  Inputs: none
		 *  Outputs: none
		 */
		void sendData();

	private:
		/**
		 * socket that links Network to UserController
		 */
		std::shared_ptr<TCPServerSocket> m_socket;
		/**
		 * buffer between Network and ManualProcessor
		 */
		std::shared_ptr<CommandBuffer> m_in_buffer;
		/**
		 * buffer that holds data to send back to UserController
		 */
		std::shared_ptr<DataBuffer> m_out_buffer;
};

#endif /* NETWORK_H_ */
