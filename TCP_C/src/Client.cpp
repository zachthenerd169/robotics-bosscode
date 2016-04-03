//
//  Client.cpp
//  
//
//  Created by Stephanie Smith on 2/28/16.
#include "headers/Client.hpp"

Client::Client(const string servAddress, unsigned short servPort)
{
    std::cout<<servAddress<<": "<<servPort<<std::endl;
    m_sock = new TCPSocket(servAddress, servPort); //constructing socket
    m_servPort=servPort;
    m_servAddress=servAddress;
}
bool Client::sendToServer(std::string message)
{
    #if DEBUG
        std::cout<<"client sending message"<<message<<std::endl;
    #endif
    const char* m=message.std::string::c_str(); //so we can use the practical socket libaray
    try
    {
        m_sock->send(m, strlen(m)); //send message to server
        #if DEBUG
            echoMessage(strlen(m));
        #endif
        return true;
    }
    catch(SocketException &e)
    {
        cerr << e.what() << endl;
        return false;
    }
}
void Client::echoMessage(unsigned int bufferSize)
{
    char echoBuffer[bufferSize+1]; //createing a buffer that can capture the message received back from the server
    int bytesReceived = 0;  // Bytes read on each recv()
    int totalBytesReceived = 0;  // Total bytes read
    while (totalBytesReceived < bufferSize)
    {
        std::cout << "Echoed: ";  // Setup to print the echoed string
        // Receive up to the buffer size bytes from the sender
        if ((bytesReceived = (m_sock->recv(echoBuffer, bufferSize+1))) <= 0)
        {
            cerr << "Unable to read";
            exit(1);
        }
        totalBytesReceived += bytesReceived;     // Keep tally of total bytes
        echoBuffer[bytesReceived] = '\0';        // Terminate the string!
        cout <<echoBuffer;
    }
    std::cout << std::endl;

}
//used to receive data from server
string Client::receiveMessageFromServer(unsigned int bufferSize)
{
    return "test";
    //implement
}