//
//  Client.cpp
//  
//
//  Created by Stephanie Smith on 2/28/16.

#include "Client.hpp"

bool Client::sendToServer(const char* message)
{
    /*int bufferSize=strlen(message)-strlen("ard-");
    //int bufferSize= arduino ? (strlen(message) + strlen("Arduino received: "))-3 : strlen(message); //I think I need to subtract 3 b/c I'm double counting spaces
    std::cout <<"buffer size: " <<bufferSize << std::endl;
    try
    {
        m_sock.send(message, strlen(message)); //send message to server
        echoMessage(bufferSize);
        return true;
    }
    catch(SocketException &e)
    {
        cerr << e.what() << endl;
        return false;
    }*/
    return false;
}
void Client::echoMessage(unsigned int bufferSize)
{
    /*char echoBuffer[bufferSize+1]; //createing a buffer that can capture the message received back from the server
    int bytesReceived = 0;  // Bytes read on each recv()
    int totalBytesReceived = 0;  // Total bytes read
    while (totalBytesReceived < bufferSize)
    {
        std::cout << "Echoed: ";  // Setup to print the echoed string
        // Receive up to the buffer size bytes from the sender
        if ((bytesReceived = (m_sock.recv(echoBuffer, bufferSize+1))) <= 0)
        {
            cerr << "Unable to read";
            exit(1);
        }
        totalBytesReceived += bytesReceived;     // Keep tally of total bytes
        echoBuffer[bytesReceived] = '\0';        // Terminate the string!
        cout <<echoBuffer;
    }
    std::cout << std::endl;*/

}
//used to receive data from server
string Client::receiveMessageFromServer(unsigned int bufferSize)
{
    return "test";
    //implement
}


