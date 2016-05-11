#include <memory> //for smart pointer
#include <iostream>

#include "../Network.h"
#include "../CommandBuffer.h"
#include "../lib/PracticalSocket.h" //for m_socket
#include "../DataBuffer.h"


int main(int argc, char** argv)
{
	DataBuffer* network_databuffer = new DataBuffer;
	CommandBuffer* network_commandbuffer = new CommandBuffer;
	unsigned int port=1024; 
	TCPServerSocket* socket = new TCPServerSocket(1025); //data that we need to test constructors

	Network network(port, network_commandbuffer, network_databuffer); //testing first constructor
	Network network2(socket, network_commandbuffer, network_databuffer); //testing 2nd constructor
	Network network3; //testing 3rd constructor

	return EXIT_SUCCESS;
}


