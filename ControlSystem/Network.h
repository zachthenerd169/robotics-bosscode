/*
 * Network.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 * Class Description:
 *
 * -- maybe ManualProcessor should have a network, otherwise how will Network know when
 *    to send sensor data back to the user?
 */

#include "lib/PracticalSocket.h" //for m_socket

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
		Network(std::string address, unsigned short port, CommandBuffer* in_buffer, DataBuffer* out_buffer):
				m_socket(new TCPSocket(address, port)), m_in_buffer(in_buffer), m_out_buffer(out_buffer){}
		/**
		 * Description:
		 * Inputs:
		 * Outputs:
		 */
		Network(TCPSocket* socket, CommandBuffer* in_buffer, DataBuffer* out_buffer):
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
		 *  			data or debugging information
		 *  Inputs: none
		 *  Outputs: none
		 */
		void sendData();

	private:
		TCPSocket* m_socket;
		CommandBuffer* m_in_buffer;
		DataBuffer* m_out_buffer;
};

#endif /* NETWORK_H_ */
