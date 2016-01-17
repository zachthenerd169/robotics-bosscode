//
//  Server.cpp
//  Created by Stephanie Smith on 1/14/16.
//
//  Description: server (running on NUC) will communicate with arduino to control robot
//  To Compile: g++ -o Server.exe Server.cpp PracticalSocket.cpp arduino-serial-lib.cpp
//  To Run: ./Server.exe 'Server's Port Number'

#include "PracticalSocket.h"  // For Socket, ServerSocket, and SocketException
#include <iostream>           // For cerr and cout
#include <cstdlib>            // For atoi()
#include "Server.hpp"
#include "arduino-serial-lib.h"

#define BAUDRATE 9600 // default baudrate
#define BUF_MAX 256   // default max buffer size
#define TIMEOUT 5000 // default timeout

const unsigned int RCVBUFSIZE = 50; // Size of receive buffer


void handleClient(TCPSocket *sock); //prototypes
string writeToArduino(char* message);

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
    cout<<"Server received: "<<buffer<<endl;
    //string str = string(buffer); //I don't think we need to do that
    //str.resize(recvMsgSize);
    //cout<<str<<endl;
    writeToArduino(buffer);
    memset(buffer, 0, RCVBUFSIZE); //clearing the buffer for next time
    delete sock;

    
}
/**
 * Input: message to send to arduino
 * Output: message sent to arduino (pass this back to the client)
 */
string writeToArduino(char* message)
{
    int fd=-1; //status
    const char* port="/dev/cu.usbmodem1411"; //default for stephanie's laptop
    const char* test_message="hello arduino!";
    int rc; //status
    
    char buf[BAUDRATE];
    
    char eolchar = '\n'; //when receive messages line by line
    
    printf("setting baud rate to %d\n", BAUDRATE);
    //printf("setting serial port to %s\n", port);
    cout<<"setting serial port to: "<<port<<endl;
    
    fd = serialport_init(port, BAUDRATE); //opening port
    (fd == -1) ? cout<< "couldn't open port" << endl : cout<< "opened port " << port << endl;
    serialport_flush(fd);
    
    fd==-1 ? cout<<"serial port not opened"<<endl : printf("sending message: %s\n", message); //sending test message
    
    rc = serialport_write(fd, message);
    if(rc==-1) perror("error writing");
    
    printf("receiving messages:\n");
    for(int i=0; i<2; i++) //two messages to read
    {
        if( fd == -1) perror("serial port not opened"); //receiving message sent    back by the arduino
        memset(buf,0,BUF_MAX); //clearing buffer
        serialport_read_until(fd, buf, eolchar, BUF_MAX, TIMEOUT);
        printf("%s", buf);
    }
    return "test";
     
    //return "test";
}
