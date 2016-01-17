//
//  Server.cpp
//  Created by Stephanie Smith on 1/14/16.
//
//  Description: server (running on NUC) will communicate with arduino to control robot
//  To Compile: g++ -o Server.exe Server.cpp PracticalSocket.cpp
//  To Run: ./Server.exe 'Server's Port Number'

#include "PracticalSocket.h"  // For Socket, ServerSocket, and SocketException
#include <iostream>           // For cerr and cout
#include <cstdlib>            // For atoi()
#include "Server.hpp"

const unsigned int RCVBUFSIZE = 50; // Size of receive buffer


void handleClient(TCPSocket *sock); //prototypes
string writeToArduino(string message);

int main(int argc, char *argv[])
{
    if (argc != 2) //Test for correct number of arguments
    {
        cerr << "Usage: " << argv[0] << " <Server Port>" << endl;
        exit(1);
    }
    unsigned short servPort = atoi(argv[1]); //First arg: local port
    try
    {
        cout<<"server running"<<endl;
        TCPServerSocket servSock(servPort);  //Server Socket object
        for (;;) {handleClient(servSock.accept()); }  // Wait for a client to connect
    
    }
    catch (SocketException &e)
    {
        cerr << e.what() << endl;
        exit(1);
    }
    return 0;
}
/**
 * Input: socket opened by server
 **/
void handleClient(TCPSocket *sock)
{
    cout << "Handling client ";
    try{cout << sock->getForeignAddress() << ": ";}
    catch (SocketException e){cerr << "Unable to get foreign address" << endl;}
    
    try{cout << sock->getForeignPort() << endl;}
    catch (SocketException e){cerr << "Unable to get foreign port" << endl;}
    
    // Send received string and receive again until the end of transmission
    char buffer[RCVBUFSIZE];
    int recvMsgSize;

    while ((recvMsgSize = sock->recv(buffer, RCVBUFSIZE)) > 0) //Zero means end of transmission
    {
       sock->send(buffer, recvMsgSize);  //Echo message back to client
    }
    cout<<buffer<<endl;
    //string str = string(buffer); //I don't think we need to do that
    //str.resize(recvMsgSize);
    //cout<<str<<endl;
    memset(buffer, 0, RCVBUFSIZE); //clearing the buffer for next time
    delete sock;
    
}
/**
 * Input: message to send to arduino
 * Output: message sent to arduino (pass this back to the client)
 */
string writeToArduino(string message)
{
    return "test";
}
