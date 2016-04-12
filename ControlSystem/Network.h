/*
 * Network.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 * Class Description:
 *
 */

#include "lib/PracticalSocket.h" //for m_socket
#include <memory> //for smart pointer

#ifndef NETWORK_H_
#define NETWORK_H_

class Network
{
	public:
		/**
		 * Description:
		 * Inputs:
		 * Outputs:
		 */
		Network(std::string address, unsigned short port, const CommandBuffer& in_buffer, DataBuffer& out_buffer):
				m_socket(new TCPSocket(address, port)), m_in_buffer(in_buffer), m_out_buffer(out_buffer){}
		/**
		 * Description:
		 * Inputs:
		 * Outputs:
		 */
		Network(TCPSocket& socket, CommandBuffer& in_buffer, DataBuffer& out_buffer):
			m_socket(socket), m_in_buffer(in_buffer), m_out_buffer(out_buffer){}
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
		std::shared_ptr<TCPSocket> m_socket;
		std::shared_ptr<CommandBuffer> m_in_buffer;
		std::shared_ptr<DataBuffer> m_out_buffer;
};

#endif /* NETWORK_H_ */
