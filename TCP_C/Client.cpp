//
//  Client.cpp
//  
//
//  Created by Stephanie Smith on 2/28/16.

#include "Client.hpp"
#include "PracticalSocket.h"  // For Socket, ServerSocket, and SocketException
#include <string.h>           // For user inputs
#include <iostream>           // For cerr and cout


void Client::displayMainMenu()
{
    std::cout<<"\nUofI Robotic's Control Menu: "<<std::endl;
    std::cout<<"1) CONTROL ROBOT\n2) Change Server's IP Address\n3) Change Server's Port Number\n4) Send Test Message To Server WITHOUT Arduino\n5) Send Test Message To Server WITH Arduino\n6) Quit Program\nEnter a number that is 1-6"<<endl;
}
void Client::displayRobotMenu()
{
    std::cout<<"\nMODE KEY: DESIRED ACTION <user input>\nSTOP ROBOT: <1>\nMOVE STRAIGHT FORWARD: <2 powerLevel>\nMOVE STRAIGHT REVERSE: <3 powerLevel>\nTURN RIGHT: <4 powerLevel>\nTURN LEFT: <5 powerLevel>\nDIGGER DROP: <6>\nRAISE DIGGER: <7>\nDUMP BUCKET: <8>\nLOWER BUCKET: <9>\nREQUEST DATA <10>\n\n"<<std::endl;
    std::cout<<"input 'help' to view mode key\ninput'exit' to quit\notherwise enter the integer that corresponds to the desired command"<<std::endl;
}
void Client::displayRequestMenu()
{
    std::cout<<"1) Get Image\n2) Get Obstacle Info\n3) Get esitmated distance\n4) Quit\n"<<std::endl;
}
/**
 *
 **/
bool Client::sendToServer(const char* message)
{
    int bufferSize=strlen(message)-strlen("ard-");
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
        if ((bytesReceived = (m_sock.recv(echoBuffer, bufferSize+1))) <= 0)
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
string Client::receiveMessageFromServer(unsigned int bufferSize)
{
    return "test";
    //implement
}


