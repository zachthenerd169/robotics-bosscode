#include "../UserController.h"
#include <iostream>
#include <cstring>

bool UserController::sendData(std::string data)
{
	std::cout<<"sending: "<<data<<std::endl;
    try
    {
        const char* packet=data.c_str();
        m_socket -> send(packet, strlen(packet)); //send message to server
        return true;
    }
    catch(SocketException &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

}
std::string UserController::receiveData()
{
    //TODO: NEED TO MAKE SURE THAT THIS IS AN ENTIRE PACKET
    const unsigned int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE]; //createing a buffer that can capture the message received back from the server
    int bytes_received = 0;  // Bytes read on each recv()
    int total_bytes_received = 0;  // Total bytes read
    while (total_bytes_received < BUFFER_SIZE)
    {  
        // Setup to print the echoed string
        // Receive up to the buffer size bytes from the sender
        // bytes_received == 0 if there is no data to be received, 
        // bytes_received == -1 if there was some sort of error
        if ((bytes_received = (m_socket->recv(buffer, BUFFER_SIZE))) <= 0)
        {
            //std::cerr << "Unable to read"<<std::endl;
            //exit(1);
            return ""; //return an empty string is nothing can be read
        }
        total_bytes_received += bytes_received; // Keep tally of total bytes
        buffer[bytes_received] = '\0';  // Terminate the string!
    }
    return string(buffer); //return the message sent back from the server
}



