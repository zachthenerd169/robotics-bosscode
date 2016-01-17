//
//  Server.cpp
//  Created by Stephanie Smith on 1/14/16.
//
//  Description: server (running on NUC) will communicate with arduino to control robot
//  To Compile: g++ -o Server.exe Server.cpp PracticalSocket.cpp
//  To Run: ./Client.exe 'Server's Port Number'

#include "PracticalSocket.h"  // For Socket, ServerSocket, and SocketException
#include <iostream>           // For cerr and cout
#include <cstdlib>            // For atoi()
#include "Server.hpp"

void handleClient(TCPSocket *sock); //prototypes

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

// TCP client handling function
void handleClient(TCPSocket *sock) {
    const unsigned int RCVBUFSIZE = 32;    // Size of receive buffer
    //cout<<"test!";
    cout << "Handling client ";
    try {
        cout << sock->getForeignAddress() << ":";
    } catch (SocketException e) {
        cerr << "Unable to get foreign address" << endl;
    }
    try {
        cout<<"test1";
        cout << sock->getForeignPort();
    } catch (SocketException e) {
        cerr << "Unable to get foreign port" << endl;
    }
    cout << endl;
    
    // Send received string and receive again until the end of transmission
    char echoBuffer[RCVBUFSIZE];
    int recvMsgSize;
    //cout<<"test"<<endl;
    while ((recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE)) > 0) { // Zero means// end of transmission
        //std:cout<<echoBuffer
        // Echo message back to client
        sock->send(echoBuffer, recvMsgSize);
        
    }
    cout<<"test2"<<endl;
    cout<<echoBuffer<<endl;
    delete sock;
}
