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
char* writeToArduino(const char* message);

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
    memset(buffer, 0, RCVBUFSIZE); //clearing the buffer for next time
    while ((recvMsgSize = sock->recv(buffer, RCVBUFSIZE)) > 0) //Zero means end of transmission
    {
        cout<<"Server received: "<<buffer<<endl;
        string str = string(buffer);
        cout<<"str is " << buffer<<endl;
        if(str.substr(0,4).compare("ard-")==0)
        {
            str=str.substr(4, recvMsgSize);
            const char *message = str.c_str();
            char *ardMessage=writeToArduino(message);
            cout<<"ardMessage is: "<<ardMessage<<endl;
            cout<<"length of ardMessage: "<<strlen(ardMessage)<<endl;
            sock->send(ardMessage, strlen(ardMessage)); //send message returned from arduino
        }
        else{sock->send(buffer, recvMsgSize);} //send message as is
    }
    delete sock;

    
}
/**
 * Input: message to send to arduino
 * Output: message sent to arduino (pass this back to the client)
 */
char* writeToArduino(const char* message)
{
    int fd=-1; //status
    const char* port="/dev/cu.usbmodem1411"; //default for stephanie's laptop
    const char* test_message="hello arduino!";
    int rc; //status
    
    char* buf=(char*)malloc(BUF_MAX*sizeof(char));
    char eolchar = '\n'; //when receive messages line by line
    
    printf("setting baud rate to %d\n", BAUDRATE);
    cout<<"setting serial port to: "<<port<<endl;
    
    fd = serialport_init(port, BAUDRATE); //opening port
    (fd == -1) ? cout<< "couldn't open port" << endl : cout<< "opened port " << port << endl;
    serialport_flush(fd);
    
    fd==-1 ? cout<<"serial port not opened"<<endl : printf("sending message: %s\n", message); //sending test message
    
    rc = serialport_write(fd, message); //writing the to the arduino
    if(rc==-1) perror("error writing");
    
    if( fd == -1) perror("serial port not opened");
    memset(buf,0,BUF_MAX); //clearing buffer
    serialport_read_until(fd, buf, eolchar, BUF_MAX, TIMEOUT); //'Arduino received <message>'
    printf("%s", buf); //printing out what server receives from arduino
   
    return buf;
    
    //WHEN YOU DON'T HAVE AN ARDUINO JUST USE THIS
    //have to do some shit to get char*
    /*string arduinoMess = "Arduino received ";
    char *tempMess = new char[arduinoMess.length() + 1];
    strcpy(tempMess, arduinoMess.c_str());
    return strcat(tempMess, message); //returning message received from arduino (test)*/
}
