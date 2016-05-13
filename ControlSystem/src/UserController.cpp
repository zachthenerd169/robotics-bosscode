#include "../UserController.h"
#include <iostream>


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
    std::string current_message = "";
    char buffer[RCVBUFSIZE];
    int recv_msg_Size;
    bool has_start = false;
    recv_msg_size = 1; // set to one just so we enter the loop
    while(recv_msg_size > 0) //keeps reading until there is nothing left to read or there is an error
    {
        memset(buffer, 0, RCVBUFSIZE); // clear the input buffer
        recv_msg_size = m_socket->recv(buffer, RCVBUFSIZE); // get data from the socket
        // iterate over the recieved data
        for(int i=0; i<recv_msg_size; i++)
        {
            if(has_start) //i f we're recording a message
            {
                if(buffer[i] == ']') // if this is the end of the message
                {
                    // send the message to the main thread
                    //q_new_messages.push(current_message);
                    // stop recording messages
                    return current_message;
                    has_start = false;
                }
                // if this is not the end of the message
                else
                {
                    // add this character to the end of the current messsage
                    current_message += buffer[i];
                }
            }
            // if we recieve a new start character
            if(buffer[i] == '[')
            {
                // start recording
                hasStart = true;
               // reset the current message
               currentMessage = "";
            } // end if
        } // end for
    } // end while
    return ""; //return nothing if there was an erro or there were no messages to be received
}



